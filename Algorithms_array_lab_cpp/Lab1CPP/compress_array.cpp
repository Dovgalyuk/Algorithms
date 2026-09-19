#include "array.h"

#include <fstream>
#include <iostream>
#include <utility>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: Lab1CPPCompress INPUT_FILE\n";
        return 2;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open input file\n";
        return 1;
    }

    std::size_t size = 0;
    if (!(input >> size))
    {
        std::cerr << "Cannot read array size\n";
        return 1;
    }

    Array<long long> values(size);
    for (std::size_t i = 0; i < size; ++i)
    {
        long long value = 0;
        if (!(input >> value))
        {
            std::cerr << "Not enough array values\n";
            return 1;
        }
        values.set(i, value);
    }

    long long left = 0;
    long long right = 0;
    if (!(input >> left >> right))
    {
        std::cerr << "Cannot read interval bounds\n";
        return 1;
    }
    if (left > right)
        std::swap(left, right);

    std::size_t write_index = 0;
    for (std::size_t read_index = 0; read_index < size; ++read_index)
    {
        const long long value = values.get(read_index);
        if (value < left || value > right)
        {
            values.set(write_index, value);
            ++write_index;
        }
    }

    while (write_index < size)
    {
        values.set(write_index, 0);
        ++write_index;
    }

    for (std::size_t i = 0; i < size; ++i)
    {
        if (i != 0)
            std::cout << ' ';
        std::cout << values.get(i);
    }
    std::cout << '\n';
    return 0;
}