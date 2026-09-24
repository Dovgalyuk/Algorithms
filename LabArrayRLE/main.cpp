#include <fstream>
#include <iostream>

#include "array.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: LabArrayRLE <input_file>\n";
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

    if (array.size() == 0)
        return 0;

    size_t i = 0;

    while (i < array.size())
    {
        const int value = array.get(i);
        size_t count = 1;

        while (i + count < array.size()
            && array.get(i + count) == value)
        {
            ++count;
        }

        std::cout << value << ' ' << count;

        i += count;

        if (i < array.size())
            std::cout << ' ';
    }

    std::cout << '\n';

    return 0;
}