import argparse
import csv
import io
import math
from pathlib import Path
import statistics
import subprocess


def main():
    parser = argparse.ArgumentParser(description="Compare insertion of preloaded pairs into three containers")
    parser.add_argument("--generator", type=Path, required=True)
    parser.add_argument("--program", type=Path, required=True)
    parser.add_argument("--output", type=Path, default=Path("benchmark-results"))
    parser.add_argument("--sizes", type=int, nargs="+",
                        default=[1000, 10000, 100000, 500000, 1000000])
    parser.add_argument("--repeats", type=int, default=3)
    args = parser.parse_args()
    if args.repeats <= 0 or any(size <= 0 for size in args.sizes):
        parser.error("sizes and repeats must be positive")
    generator = args.generator.resolve()
    program = args.program.resolve()
    if not generator.is_file() or not program.is_file():
        parser.error("build the generator and benchmark program first")

    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    data = output / "data"
    data.mkdir(exist_ok=True)
    names = ["BWA", "map", "unordered_map"]

    with (output / "runs.csv").open("w", newline="", encoding="utf-8") as raw_file, \
         (output / "medians.csv").open("w", newline="", encoding="utf-8") as median_file:
        raw = csv.writer(raw_file)
        summary = csv.writer(median_file)
        raw.writerow(["pairs", "run", "position", "container", "size", "seconds"])
        summary.writerow(["pairs", "container", "median_seconds", "min_seconds", "max_seconds"])

        for size in sorted(set(args.sizes)):
            filename = data / f"input_{size}.txt"
            subprocess.run([str(generator), str(filename), str(size)], check=True, timeout=120)
            subprocess.run([str(program), str(filename)], check=True,
                           stdout=subprocess.DEVNULL, timeout=300)
            times = {name: [] for name in names}

            for run in range(args.repeats):
                first = run % 3
                result = subprocess.run([str(program), str(filename), str(first)],
                                        check=True, capture_output=True, text=True, timeout=300)
                rows = list(csv.DictReader(io.StringIO(result.stdout)))
                order = names[first:] + names[:first]
                if [row["container"] for row in rows] != order:
                    raise ValueError("unexpected benchmark output")

                for position, row in enumerate(rows, start=1):
                    seconds = float(row["seconds"])
                    if int(row["pairs"]) != size or int(row["size"]) != size:
                        raise ValueError(f"wrong number of pairs for {row['container']}")
                    if not math.isfinite(seconds) or seconds < 0:
                        raise ValueError("invalid elapsed time")
                    times[row["container"]].append(seconds)
                    raw.writerow([size, run + 1, position, row["container"], size, seconds])
                raw_file.flush()
                print(f"{size} pairs: run {run + 1}/{args.repeats}", flush=True)

            for name in names:
                values = times[name]
                summary.writerow([size, name, statistics.median(values), min(values), max(values)])
            median_file.flush()

    print(f"Results: {output}")


if __name__ == "__main__":
    main()
