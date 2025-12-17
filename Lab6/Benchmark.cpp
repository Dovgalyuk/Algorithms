#include "Benchmark.h"

Matrix Benchmark::generateChain(const int n) {
    if (n <= 0 || n > BENCHMARK_MAX_N) {
        throw std::runtime_error("Invalid chain size for benchmark");
    }

    Vector<int> dims;
    dims.reserve(n + 1);

    for (auto i{ 0 }; i <= n; ++i) {
        dims.push_back(10 + (i % 10) * 5);
    }

    Matrix matrices;
    matrices.reserve(n);

    for (auto i{ 0 }; i < n; ++i) {
        matrices.emplace_back(dims[i], dims[i + 1]);
    }

    return matrices;
}

void Benchmark::run(const bool writeToFile, const int repeats, const int benchmarkRuns, const std::string &outputFileName) {
    std::ofstream csv;
    if (writeToFile) {
        csv.open(outputFileName);
        if (!csv) {
            throw std::runtime_error("Cannot open results.csv");
        }
        csv << "n,exhaustive_avg_ns,dp_avg_ns\n";
    }

    std::cout << "n\tExhaustive (ns)\tDP (ns)\n";
    std::cout << std::string(45, '-') << "\n";

    for (auto n{2}; n <= benchmarkRuns; ++n) {
        auto matrices = generateChain(n);
        MatrixChain chain(matrices);

        double exhaustiveSum{};
        for (auto r{0}; r < repeats; ++r) {
            ExhaustiveSolver exhaustive(chain);
            auto t1 = Clock::now();
            exhaustive.solve();
            auto t2 = Clock::now();
            exhaustiveSum += ns(t2 - t1).count();
        }


        double dpSum{};
        for (auto r{0}; r < repeats; ++r) {
            DPSolver dp(chain);
            auto t1 = Clock::now();
            dp.solve();
            auto t2 = Clock::now();
            dpSum += ns(t2 - t1).count();
        }

        const double exhaustiveAvg = exhaustiveSum / repeats;
        const double dpAvg = dpSum / repeats;

        std::cout << n << "\t";

        std::cout << exhaustiveAvg;
        std::cout << "\t\t" << dpAvg << "\n";

        if (writeToFile) {
            csv << n << "," << exhaustiveAvg << "," << dpAvg << "\n";
        }
    }

    std::cout << "\nBenchmark completed." << std::endl;
    if (writeToFile) {
        std::cout << "Results saved to " + outputFileName << std::endl;
    }
}
