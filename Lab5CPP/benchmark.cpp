#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

#include "avl.h"

using namespace std;
using Clock = chrono::steady_clock;

double measure_avl(const vector<string> &values, size_t count, size_t expected)
{
    AVLTree *tree = avl_create();
    try
    {
        auto start = Clock::now();
        for (size_t i = 0; i < count; ++i)
            avl_insert(tree, values[i]);
        auto finish = Clock::now();

        if (avl_size(tree) != expected || !avl_check(tree))
            throw runtime_error("AVL result is incorrect");
        avl_delete(tree);
        return chrono::duration<double, milli>(finish - start).count();
    }
    catch (...)
    {
        avl_delete(tree);
        throw;
    }
}

double measure_set(const vector<string> &values, size_t count, size_t expected)
{
    set<string> container;
    auto start = Clock::now();
    for (size_t i = 0; i < count; ++i)
        container.insert(values[i]);
    auto finish = Clock::now();

    if (container.size() != expected)
        throw runtime_error("set result is incorrect");
    return chrono::duration<double, milli>(finish - start).count();
}

double measure_unordered_set(const vector<string> &values, size_t count, size_t expected)
{
    unordered_set<string> container;
    auto start = Clock::now();
    for (size_t i = 0; i < count; ++i)
        container.insert(values[i]);
    auto finish = Clock::now();

    if (container.size() != expected)
        throw runtime_error("unordered_set result is incorrect");
    return chrono::duration<double, milli>(finish - start).count();
}

double median(vector<double> values)
{
    sort(values.begin(), values.end());
    size_t middle = values.size() / 2;
    if (values.size() % 2 == 0)
        return (values[middle - 1] + values[middle]) / 2;
    return values[middle];
}

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 3 && argc != 4)
            throw runtime_error("Usage: Lab5CPPBenchmark input.txt result.csv [repeats]");

        int repeats = 3;
        if (argc == 4)
        {
            string argument = argv[3];
            if (argument.empty() || argument.find_first_not_of("0123456789") != string::npos)
                throw runtime_error("Invalid repeats");
            repeats = stoi(argument);
            if (repeats < 1 || repeats > 100)
                throw runtime_error("Invalid repeats");
        }

        ifstream input(argv[1]);
        if (!input)
            throw runtime_error("Cannot open input file");
        vector<string> values;
        string line;
        while (getline(input, line))
        {
            if (!line.empty() && line.back() == '\r')
                line.pop_back();
            values.push_back(line);
        }
        if (input.bad())
            throw runtime_error("Cannot read input file");
        if (values.empty())
            throw runtime_error("Empty input file");

        vector<size_t> sizes;
        for (size_t count : {1000u, 5000u, 10000u, 25000u, 50000u,
                            100000u, 250000u, 500000u, 1000000u})
            if (count < values.size())
                sizes.push_back(count);
        sizes.push_back(values.size());

        ofstream output(argv[2]);
        if (!output)
            throw runtime_error("Cannot open result file");
        output << "count,avl_ms,set_ms,unordered_set_ms\n" << fixed << setprecision(6);
        cout << fixed << setprecision(3);

        for (size_t count : sizes)
        {
            size_t expected;
            {
                unordered_set<string> unique;
                for (size_t i = 0; i < count; ++i)
                    unique.insert(values[i]);
                expected = unique.size();
            }

            vector<double> times[3];
            for (int repeat = 0; repeat < repeats; ++repeat)
            {
                for (int offset = 0; offset < 3; ++offset)
                {
                    int container = (repeat + offset) % 3;
                    if (container == 0)
                        times[0].push_back(measure_avl(values, count, expected));
                    else if (container == 1)
                        times[1].push_back(measure_set(values, count, expected));
                    else
                        times[2].push_back(measure_unordered_set(values, count, expected));
                }
            }

            double avl = median(times[0]);
            double ordered = median(times[1]);
            double unordered = median(times[2]);
            output << count << ',' << avl << ',' << ordered << ',' << unordered << '\n';
            cout << count << ": AVL=" << avl << " ms, set=" << ordered
                 << " ms, unordered_set=" << unordered << " ms" << endl;
        }

        output.close();
        if (!output)
            throw runtime_error("Cannot write result file");
        return 0;
    }
    catch (const exception &error)
    {
        cerr << error.what() << '\n';
        return 1;
    }
}
