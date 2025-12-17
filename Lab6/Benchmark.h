#pragma once

#include <iostream>
#include <fstream>
#include "utility.h"
#include "MatrixChain.h"
#include "ExhaustiveSolver.h"
#include "DPSolver.h"

constexpr int BENCHMARK_MAX_N = 20;

class Benchmark {
public:
    static Matrix generateChain(int n);
    static void run(bool writeToFile = true, int repeats = 5, int benchmarkRuns = 3, const std::string& outputFileName = "results.csv");
};
