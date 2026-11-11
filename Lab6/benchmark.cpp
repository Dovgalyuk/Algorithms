#include "matrix_chain.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>

using namespace std;

double measureBatch(const Dimensions& dimensions, bool useDP,
                    size_t runs, long long expected)
{
    auto start = chrono::steady_clock::now();
    for (size_t i = 0; i < runs; ++i)
    {
        Result result;
        if (useDP)
            result = solveDynamic(dimensions);
        else
            result = solveBruteForce(dimensions);
        if (result.cost != expected)
            throw runtime_error(u8"Результаты алгоритмов не совпали.");
    }
    auto finish = chrono::steady_clock::now();
    return chrono::duration<double, milli>(finish - start).count();
}

double measure(const Dimensions& dimensions, bool useDP,
               size_t& runs, long long expected)
{
    runs = 1;
    while (measureBatch(dimensions, useDP, runs, expected) < 20.0 && runs < 1048576)
        runs *= 2;

    double times[5];
    for (int i = 0; i < 5; ++i)
        times[i] = measureBatch(dimensions, useDP, runs, expected) / static_cast<double>(runs);
    sort(times, times + 5);
    return times[2];
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << u8"Использование: Lab6Benchmark выходной.csv\n";
        return 1;
    }

    try
    {
        ofstream output(argv[1]);
        if (!output)
            throw runtime_error(u8"Не удалось открыть выходной файл.");

        mt19937 generator(42);
        Dimensions allDimensions(641);
        for (long long& dimension : allDimensions)
            dimension = 10 + generator() % 91;

        const size_t sizes[] = {2, 4, 6, 8, 10, 12, 14, 16, 18,
                               20, 40, 80, 160, 320, 640};
        output << "n,brute_ms,dp_ms,brute_runs,dp_runs\n";
        output << fixed << setprecision(9);
        for (size_t n : sizes)
        {
            Dimensions dimensions(allDimensions.begin(), allDimensions.begin() + n + 1);
            long long expected = solveDynamic(dimensions).cost;
            size_t bruteRuns = 0, dpRuns = 0;
            double bruteTime = 0;
            if (n <= 18)
                bruteTime = measure(dimensions, false, bruteRuns, expected);
            double dpTime = measure(dimensions, true, dpRuns, expected);

            output << n << ',';
            if (bruteRuns != 0)
                output << bruteTime;
            output << ',' << dpTime << ',';
            if (bruteRuns != 0)
                output << bruteRuns;
            output << ',' << dpRuns << '\n';
            output.flush();
            if (!output)
                throw runtime_error(u8"Ошибка записи результатов.");
            cout << "n = " << n << endl;
        }
    }
    catch (const exception& error)
    {
        cerr << u8"Ошибка: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
