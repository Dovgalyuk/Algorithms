import csv
import math
import sys
from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt


folder = Path(sys.argv[1]) if len(sys.argv) > 1 else Path(__file__).parent / "results"
orders = ["ascending", "descending", "random"]
titles = ["По возрастанию", "По убыванию", "Случайный порядок"]
columns = ["avl_ms", "set_ms", "unordered_set_ms"]
names = ["АВЛ-дерево", "std::set", "std::unordered_set"]
colors = ["#247c88", "#cf6d32", "#7255a2"]
datasets = []

for order in orders:
    with (folder / f"{order}.csv").open(encoding="utf-8", newline="") as source:
        rows = list(csv.DictReader(source))
    datasets.append({column: [float(row[column]) for row in rows]
                     for column in ["count"] + columns})

plt.rcParams.update({"font.family": "DejaVu Sans", "font.size": 10,
                     "axes.spines.top": False, "axes.spines.right": False})

figure, axes = plt.subplots(1, 3, figsize=(15, 4.8), layout="constrained")
figure.suptitle("Вставка строк: АВЛ-дерево и стандартные контейнеры", fontsize=16)
for axis, data, title in zip(axes, datasets, titles):
    x = [count / 1_000_000 for count in data["count"]]
    for column, name, color in zip(columns, names, colors):
        axis.plot(x, data[column], marker="o", markersize=4, linewidth=2,
                  label=name, color=color)
    axis.set_title(title)
    axis.set_xlabel("Количество строк, млн")
    axis.set_ylabel("Время вставки, мс")
    axis.set_xlim(left=0)
    axis.set_ylim(bottom=0)
    axis.grid(alpha=0.2)
    axis.legend(fontsize=9)
figure.savefig(folder / "insertion_time.png", dpi=180)
plt.close(figure)

figure, axes = plt.subplots(1, 3, figsize=(15, 4.8), layout="constrained")
figure.suptitle("Время с учётом ожидаемого количества операций", fontsize=16)
for axis, column, name in zip(axes, columns, names):
    for data, title, color in zip(datasets, titles, colors):
        counts = data["count"]
        divisor = counts if column == "unordered_set_ms" else [n * math.log2(n) for n in counts]
        normalized = [time * 1_000_000 / scale for time, scale in zip(data[column], divisor)]
        axis.plot([n / 1_000_000 for n in counts], normalized,
                  marker="o", markersize=4, linewidth=2, label=title, color=color)
    axis.set_title(name)
    axis.set_xlabel("Количество строк, млн")
    axis.set_ylabel("T / N, нс" if column == "unordered_set_ms" else "T / (N · log₂ N), нс")
    axis.set_xlim(left=0)
    axis.set_ylim(bottom=0)
    axis.grid(alpha=0.2)
    axis.legend(fontsize=9)
figure.savefig(folder / "normalized_time.png", dpi=180)
plt.close(figure)
