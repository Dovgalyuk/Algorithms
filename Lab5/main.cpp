#include <iostream>
#include <string>
#include <vector>
#include "RobinHoodMap.h"
#include "Benchmark.h"

int main() {
    Benchmark<RobinHoodMap<std::string, std::string>>::runAllTests(
            {1000, 5000, 10'000, 80'000, 100'000, 250'000, 500'000, 1'000'000},
            "results.csv",
            42
        );

    return 0;
}
