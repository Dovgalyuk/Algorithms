import argparse
import csv
from pathlib import Path
import re
import statistics
import subprocess


def main():
    parser = argparse.ArgumentParser(description="Measure BWA checks at different input sizes")
    parser.add_argument("--generator", type=Path, required=True)
    parser.add_argument("--program", type=Path, required=True)
    parser.add_argument("--output", type=Path, default=Path("stress-results"))
    parser.add_argument("--sizes", type=int, nargs="+",
                        default=[1000, 10000, 100000, 500000, 1000000])
    parser.add_argument("--repeats", type=int, default=3)
    args = parser.parse_args()
    if args.repeats <= 0 or any(size <= 0 for size in args.sizes):
        parser.error("sizes and repeats must be positive")
    generator = args.generator.resolve()
    program = args.program.resolve()
    if not generator.is_file() or not program.is_file():
        parser.error("build the generator and stress program first")

    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    data = output / "data"
    data.mkdir(exist_ok=True)
    phases = ["insert", "find", "erase"]
    with (output / "stress_runs.csv").open("w", newline="", encoding="utf-8") as raw_file, \
         (output / "stress_medians.csv").open("w", newline="", encoding="utf-8") as median_file:
        raw = csv.writer(raw_file)
        summary = csv.writer(median_file)
        raw.writerow(["pairs", "run", "operation", "seconds"])
        summary.writerow(["pairs", "operation", "median_seconds", "min_seconds", "max_seconds"])

        for size in sorted(set(args.sizes)):
            filename = data / f"input_{size}.txt"
            subprocess.run([str(generator), str(filename), str(size)], check=True, timeout=120)
            subprocess.run([str(program), str(filename), str(size)], check=True,
                           stdout=subprocess.DEVNULL, timeout=300)
            times = {phase: [] for phase in phases}
            for run in range(args.repeats):
                result = subprocess.run([str(program), str(filename), str(size)],
                                        check=True, capture_output=True, text=True, timeout=300)
                rows = re.findall(r"^(insert|find|erase): (\d+) pairs, ([0-9.eE+-]+) seconds$",
                                  result.stdout, flags=re.MULTILINE)
                if [row[0] for row in rows] != phases or "All stress tests passed" not in result.stdout:
                    raise ValueError("unexpected stress output")
                for phase, pairs, elapsed in rows:
                    if int(pairs) != size:
                        raise ValueError("wrong number of pairs")
                    seconds = float(elapsed)
                    times[phase].append(seconds)
                    raw.writerow([size, run + 1, phase, seconds])
                raw_file.flush()
                print(f"{size} pairs: run {run + 1}/{args.repeats}", flush=True)
            for phase in phases:
                values = times[phase]
                summary.writerow([size, phase, statistics.median(values), min(values), max(values)])
            median_file.flush()
    print(f"Results: {output}")


if __name__ == "__main__":
    main()
