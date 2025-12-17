#include <fstream>
#include <iostream>
#include <ranges>
#include <string>

#include "utility.h"
#include "Benchmark.h"
#include "MatrixChain.h"
#include "DPSolver.h"
#include "ExhaustiveSolver.h"

int main(int argc, char *argv[]) {
    try {
        std::string inputFile;
        Benchmark::run();
        std::exit(0);
        for (auto i{1}; i < argc; ++i) {
            if (const std::string arg = argv[i]; arg == "--benchmark" || arg == "-b") {
                Benchmark::run();
                std::exit(0);
            } else {
                inputFile = arg;
            }
        }

        Matrix matrices;

        if (!inputFile.empty()) {
            std::ifstream fin(inputFile);
            if (!fin) {
                throw std::runtime_error("Cannot open input file: " + inputFile);
            }
            matrices = readMatrices(fin);
        }

        if (!matrices.empty()) {
            MatrixChain chain(matrices);

            ExhaustiveSolver exhaustive(chain);
            DPSolver dp(chain);

            const auto exhaustiveOp = exhaustive.solve();
            const auto dpOp = dp.solve();

            if (exhaustiveOp != dpOp) {
                throw std::runtime_error("Solve failed");
            }

            std::cout << dpOp << "\n" << dp.getExpression() << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
