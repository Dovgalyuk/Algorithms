// Читает из файла размер массива и его элементы,
// считает положительные, отрицательные и нулевые значения.

#include <fstream>
#include <iostream>

#include "array.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: Lab1CPPCount <input file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open file " << argv[1] << "\n";
        return 1;
    }

    size_t size = 0;
    if (!(input >> size))
    {
        std::cerr << "Cannot read array size\n";
        return 1;
    }

    Array arr(size);
    for (size_t i = 0; i < size; ++i)
    {
        Data value = 0;
        if (!(input >> value))
        {
            std::cerr << "Cannot read element " << i << "\n";
            return 1;
        }
        arr.set(i, value);
    }

    size_t positive = 0;
    size_t negative = 0;
    size_t zero = 0;

    for (size_t i = 0; i < arr.size(); ++i)
    {
        const Data value = arr.get(i);
        if (value > 0)
            ++positive;
        else if (value < 0)
            ++negative;
        else
            ++zero;
    }

    std::cout << "Positive: " << positive
        << " Negative: " << negative
        << " Zero: " << zero << "\n";
    return 0;
}