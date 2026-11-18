import csv
import math
import sys
from collections import defaultdict
from pathlib import Path
import matplotlib.pyplot as plt

CONTAINERS = [("splay_ms", "SplayMap"), ("map_ms", "std::map"), ("unordered_map_ms", "std::unordered_map")]
REQUIRED = {"pattern", "records", "splay_ms", "map_ms", "unordered_map_ms"}

def has_required_columns(path):
    try:
        with open(path, newline="", encoding="utf-8-sig") as f:
            header = next(csv.reader(f), [])
        return REQUIRED.issubset(set(header))
    except (OSError, UnicodeDecodeError):
        return False

def find_csv():
    folders = [Path(__file__).resolve().parent, Path.cwd()]
    for folder in folders:
        preferred = folder / "benchmark_full.csv"
        if preferred.is_file() and has_required_columns(preferred):
            return preferred
        candidates = [p for p in folder.glob("*.csv") if has_required_columns(p)]
        if candidates:
            return max(candidates, key=lambda p: p.stat().st_mtime)
    return None

def slope(xs, ys):
    lx = [math.log(x) for x in xs]
    ly = [math.log(y) for y in ys]
    n = len(lx)
    mx, my = sum(lx) / n, sum(ly) / n
    return sum((a - mx) * (b - my) for a, b in zip(lx, ly)) / sum((a - mx) ** 2 for a in lx)

def main():
    if len(sys.argv) > 1:
        source = Path(sys.argv[1])
    else:
        source = find_csv()
        if source is None:
            print("CSV not found. Put benchmark_full.csv near script or pass path.")
            return 1
    if not source.is_file():
        print("File not found:", source)
        return 1

    target = Path(sys.argv[2]) if len(sys.argv) > 2 else source.with_suffix(".png")
    data = defaultdict(list)
    with open(source, newline="", encoding="utf-8-sig") as f:
        for row in csv.DictReader(f):
            data[row["pattern"]].append((int(row["records"]), float(row["splay_ms"]), float(row["map_ms"]), float(row["unordered_map_ms"])))

    patterns = sorted(data)
    fig, axes = plt.subplots(1, len(patterns), figsize=(5 * len(patterns), 4), squeeze=False)
    print("%-8s %-20s %s" % ("pattern", "container", "p in t ~ N^p"))

    for axis, pattern in zip(axes[0], patterns):
        rows = sorted(data[pattern])
        sizes = [r[0] for r in rows]
        for index, (_, label) in enumerate(CONTAINERS, start=1):
            times = [r[index] for r in rows]
            axis.plot(sizes, times, marker="o", label=label)
            if len(sizes) >= 2:
                print("%-8s %-20s %.2f" % (pattern, label, slope(sizes, times)))
        axis.set_xscale("log")
        axis.set_yscale("log")
        axis.set_title("order: " + pattern)
        axis.set_xlabel("N")
        axis.set_ylabel("time, ms")
        axis.grid(True, which="both", alpha=0.3)
        axis.legend()

    fig.tight_layout()
    fig.savefig(target, dpi=130)
    print("Saved:", target)

if __name__ == "__main__":
    sys.exit(main())