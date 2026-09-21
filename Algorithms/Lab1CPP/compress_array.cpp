#include "array.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: Lab1CPPCompress INPUT_FILE\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open input file\n";
        return 1;
    }

    int count = 0;
    if (!(input >> count) || count < 0)
    {
        std::cerr << "Invalid array size\n";
        return 1;
    }

    try
    {
        Array<double> values(static_cast<std::size_t>(count));
        for (std::size_t i = 0; i < values.size(); ++i)
        {
            double value = 0;
            if (!(input >> value) || !std::isfinite(value))
            {
                std::cerr << "Invalid array value\n";
                return 1;
            }
            values.set(i, value);
        }

        double a = 0;
        double b = 0;
        if (!(input >> a >> b) || !std::isfinite(a) || !std::isfinite(b) || a > b)
        {
            std::cerr << "Expected interval bounds a <= b\n";
            return 1;
        }

        std::size_t next = 0;
        for (std::size_t i = 0; i < values.size(); ++i)
        {
            const double value = values.get(i);
            if (value < a || value > b)
                values.set(next++, value);
        }
        while (next < values.size())
            values.set(next++, 0);

        std::cout << std::setprecision(15);
        for (std::size_t i = 0; i < values.size(); ++i)
        {
            if (i != 0)
                std::cout << ' ';
            std::cout << values.get(i);
        }
        std::cout << '\n';
    }
    catch (const std::exception &error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}
