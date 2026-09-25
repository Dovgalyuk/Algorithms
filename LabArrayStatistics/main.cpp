#include <fstream>
#include <iostream>
#include <string>

#include "array.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: LabArrayStatistics <input_file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);

    if (!input)
    {
        std::cerr << "Cannot open input file\n";
        return 1;
    }

    size_t n;

    if (!(input >> n))
    {
        std::cerr << "Invalid array size\n";
        return 1;
    }

    Array array(n);

    for (size_t i = 0; i < n; ++i)
    {
        int value;

        if (!(input >> value))
        {
            std::cerr << "Not enough input data\n";
            return 1;
        }

        array.set(i, value);
    }

    size_t positive = 0;
    size_t negative = 0;
    size_t zero = 0;

    for (size_t i = 0; i < array.size(); ++i)
    {
        const int value = array.get(i);

        if (value > 0)
            ++positive;
        else if (value < 0)
            ++negative;
        else
            ++zero;
    }

    std::cout << "Positive: " << positive << '\n';
    std::cout << "Negative: " << negative << '\n';
    std::cout << "Zero: " << zero << '\n';

    return 0;
}