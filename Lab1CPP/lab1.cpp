
#include "array.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <vector>

void solve_sieve(const std::string& input_file,
                 const std::string& output_file)
{
    std::ifstream input(input_file);

    if (!input)
    {
        throw std::runtime_error("Cannot open input file: " + input_file);
    }

    size_t n;

    if (!(input >> n))
    {
        throw std::runtime_error("Cannot read array size");
    }

    Array* arr = array_create(n);

    for (size_t i = 0; i < n; ++i)
    {
        array_set(arr, i, static_cast<Data>(i + 1));
    }

    std::vector<bool> prime(n + 1, true);

    if (n >= 0)
    {
        prime[0] = false;
    }

    if (n >= 1)
    {
        prime[1] = false;
    }

    for (size_t p = 2; p * p <= n; ++p)
    {
        if (prime[p])
        {
            for (size_t multiple = p * p;
                 multiple <= n;
                 multiple += p)
            {
                prime[multiple] = false;
            }
        }
    }

    size_t position = 0;

    for (size_t i = 2; i <= n; ++i)
    {
        if (prime[i])
        {
            array_set(arr, position, static_cast<Data>(i));
            ++position;
        }
    }

    while (position < n)
    {
        array_set(arr, position, 0);
        ++position;
    }

    std::ofstream output(output_file);

    if (!output)
    {
        array_delete(&arr);
        throw std::runtime_error(
            "Cannot open output file: " + output_file);
    }

    for (size_t i = 0; i < n; ++i)
    {
        output << array_get(arr, i);

        if (i + 1 < n)
        {
            output << ' ';
        }
    }

    output << '\n';

    array_delete(&arr);
}

void solve_min_even_difference(const std::string& input_file,
                               const std::string& output_file)
{
    std::ifstream input(input_file);

    if (!input)
    {
        throw std::runtime_error("Cannot open input file: " + input_file);
    }

    size_t n;

    if (!(input >> n))
    {
        throw std::runtime_error("Cannot read array size");
    }

    Array* arr = array_create(n);

    for (size_t i = 0; i < n; ++i)
    {
        Data value;

        if (!(input >> value))
        {
            array_delete(&arr);

            throw std::runtime_error(
                "Not enough elements in input file");
        }

        array_set(arr, i, value);
    }

    std::set<Data> even_values;

    for (size_t i = 0; i < n; ++i)
    {
        Data value = array_get(arr, i);

        if (value % 2 == 0)
        {
            even_values.insert(value);
        }
    }

    std::ofstream output(output_file);

    if (!output)
    {
        array_delete(&arr);

        throw std::runtime_error(
            "Cannot open output file: " + output_file);
    }

    if (even_values.size() < 2)
    {
        output << "NO\n";
    }
    else
    {
        int minimum_difference = std::numeric_limits<int>::max();

        auto previous = even_values.begin();
        auto current = std::next(previous);

        while (current != even_values.end())
        {
            int difference = *current - *previous;

            if (difference < minimum_difference)
            {
                minimum_difference = difference;
            }

            previous = current;
            ++current;
        }

        output << minimum_difference << '\n';
    }

    array_delete(&arr);
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr
            << "Usage:\n"
            << "  " << argv[0]
            << " sieve <input_file> <output_file>\n"
            << "  " << argv[0]
            << " mindiff <input_file> <output_file>\n";

        return 1;
    }

    const std::string mode = argv[1];
    const std::string input_file = argv[2];
    const std::string output_file = argv[3];

    try
    {
        if (mode == "sieve")
        {
            solve_sieve(input_file, output_file);
        }
        else if (mode == "mindiff")
        {
            solve_min_even_difference(input_file, output_file);
        }
        else
        {
            std::cerr << "Unknown mode: " << mode << '\n';
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
