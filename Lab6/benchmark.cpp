#include "matrix_chain.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

using namespace std;

typedef Result (*Solver)(const Dimensions&);

struct Measurement
{
    double milliseconds;
    size_t runs;
};

static double measureBatch(Solver solver, const Dimensions& dimensions,
                           size_t runs, long long expected)
{
    vector<long long> costs(runs);
    const auto start = chrono::steady_clock::now();
    for (size_t run = 0; run < runs; ++run)
    {
        const Result result = solver(dimensions);
        costs[run] = result.cost;
    }
    const auto finish = chrono::steady_clock::now();

    for (size_t run = 0; run < runs; ++run)
    {
        if (costs[run] != expected)
        {
            throw runtime_error("Algorithms returned different costs");
        }
    }
    return chrono::duration<double, milli>(finish - start).count();
}

static Measurement measure(Solver solver, const Dimensions& dimensions,
                           long long expected)
{
    const size_t maxRuns = 1048576;
    size_t runs = 1;
    while (measureBatch(solver, dimensions, runs, expected) < 20.0
           && runs < maxRuns)
    {
        runs *= 2;
    }

    vector<double> times;
    for (int sample = 0; sample < 5; ++sample)
    {
        times.push_back(measureBatch(solver, dimensions, runs, expected)
                        / static_cast<double>(runs));
    }
    sort(times.begin(), times.end());
    return {times[2], runs};
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: Lab6Benchmark output.csv\n";
        return 1;
    }

    try
    {
        ofstream output(argv[1]);
        if (!output)
        {
            throw runtime_error("Cannot open output file");
        }

        const size_t sizes[] = {2, 4, 6, 8, 10, 12, 14, 16, 18,
                                20, 40, 80, 160, 320, 640};
        mt19937 generator(42);
        Dimensions allDimensions(641);
        for (size_t i = 0; i < allDimensions.size(); ++i)
        {
            allDimensions[i] = 10 + generator() % 91;
        }

        output << "n,brute_ms,dp_ms,brute_runs,dp_runs\n";
        output << fixed << setprecision(9);
        for (size_t n : sizes)
        {
            const Dimensions dimensions(allDimensions.begin(),
                                        allDimensions.begin() + n + 1);
            const long long expected = solveDynamic(dimensions).cost;
            Measurement brute = {0.0, 0};
            if (n <= 18)
            {
                brute = measure(solveBruteForce, dimensions, expected);
            }
            const Measurement dynamic = measure(solveDynamic, dimensions,
                                                expected);

            output << n << ',';
            if (brute.runs != 0)
            {
                output << brute.milliseconds;
            }
            output << ',' << dynamic.milliseconds << ',';
            if (brute.runs != 0)
            {
                output << brute.runs;
            }
            output << ',' << dynamic.runs << '\n';
            output.flush();
            if (!output)
            {
                throw runtime_error("Cannot write output file");
            }

            cout << "n = " << n << ": ";
            if (brute.runs != 0)
            {
                cout << "brute = " << brute.milliseconds << " ms, ";
            }
            cout << "DP = " << dynamic.milliseconds << " ms" << endl;
        }
    }
    catch (const exception& error)
    {
        cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
