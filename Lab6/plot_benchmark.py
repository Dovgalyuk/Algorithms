import argparse
import csv
from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt


def main():
    parser = argparse.ArgumentParser(description="Графики лабораторной работы 6")
    parser.add_argument("csv", type=Path, help="CSV, полученный Lab6Benchmark")
    parser.add_argument("--preview", type=Path, help="Отдельный PNG для просмотра")
    args = parser.parse_args()

    with args.csv.open(encoding="utf-8", newline="") as source:
        rows = list(csv.DictReader(source))

    if not rows:
        parser.error("CSV не содержит измерений")

    n_dp = [int(row["n"]) for row in rows]
    t_dp = [float(row["dp_ms"]) for row in rows]
    brute_rows = [row for row in rows if row["brute_ms"]]
    n_brute = [int(row["n"]) for row in brute_rows]
    t_brute = [float(row["brute_ms"]) for row in brute_rows]

    if not brute_rows or any(t <= 0 for t in t_dp + t_brute):
        parser.error("Нужны положительные времена обоих алгоритмов")

    plt.rcParams.update({"font.family": "DejaVu Sans", "font.size": 10, "svg.fonttype": "none"})
    fig, axes = plt.subplots(1, 3, figsize=(17, 6))
    fig.subplots_adjust(left=0.06, right=0.99, bottom=0.2, top=0.8, wspace=0.3)
    blue, orange = "#2463a5", "#d26b21"

    axes[0].semilogy(n_brute, t_brute, "o-", color=orange, label="Перебор")
    axes[0].semilogy(
        n_brute,
        [float(row["dp_ms"]) for row in brute_rows],
        "o-",
        color=blue,
        label="Динамическое программирование",
    )
    axes[0].set_title("Одинаковые входные данные")

    brute_reference = [t_brute[-1] * 3 ** (n - n_brute[-1]) for n in n_brute]
    axes[1].semilogy(n_brute, t_brute, "o-", color=orange, label="Перебор: замеры")
    axes[1].semilogy(
        n_brute, brute_reference, "--", color="#555555", label="Ориентир c · 3ⁿ"
    )
    axes[1].set_title("Перебор: Θ(3ⁿ)")

    dp_reference = [t_dp[-1] * (n / n_dp[-1]) ** 3 for n in n_dp]
    axes[2].loglog(n_dp, t_dp, "o-", color=blue, label="ДП: замеры")
    axes[2].loglog(
        n_dp, dp_reference, "--", color="#555555", label="Ориентир c · n³"
    )
    axes[2].set_title("Рекурсия с запоминанием: Θ(n³)")

    for axis in axes:
        axis.set_xlabel("Количество матриц n")
        axis.set_ylabel("Время одного решения, мс")
        axis.grid(True, which="both", alpha=0.22)
        axis.legend(fontsize=8, loc="best")

    fig.suptitle(
        "Умножение цепочки матриц: медиана пяти серий измерений\n"
        "Без чтения, генерации и печати; пунктир нормирован по последней точке",
        fontsize=13, y=0.95,
    )
    fig.text(
        0.5, 0.07,
        "Вызовы перебора: 3ⁿ⁻¹. Проверки разбиений в ДП: n(n − 1)(n + 1)/6.\n"
        "Память обеих программ: Θ(n²), включая таблицу для восстановления скобок.",
        ha="center", va="center", fontsize=10,
    )
    destination = args.csv.with_suffix(".svg")
    fig.savefig(destination, facecolor="white", metadata={"Date": None})
    content = destination.read_text(encoding="utf-8")
    destination.write_text("\n".join(line.rstrip() for line in content.splitlines()) + "\n",
                           encoding="utf-8")
    print(destination)
    if args.preview:
        fig.savefig(args.preview, dpi=180, facecolor="white")
        print(args.preview)
    plt.close(fig)


if __name__ == "__main__":
    main()
