#include "array.h"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "usage: indivisible <input_file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);

    if (!input)
    {
        std::cout << "cannot open file\n";
        return 1;
    }

    int n;

    if (!(input >> n) || n < 0)
    {
        std::cout << "invalid array size\n";
        return 1;
    }

    Array* arr = array_create(static_cast<size_t>(n));

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        Data value;

        if (!(input >> value))
        {
            std::cout << "invalid array element\n";
            array_delete(arr);
            return 1;
        }

        array_set(arr, i, value);
    }

    bool found = false;

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        Data value = array_get(arr, i);
        bool has_divisor = false;

        for (size_t j = 0; j < array_size(arr); ++j)
        {
            if (i == j)
                continue;

            Data divisor = array_get(arr, j);

            if (divisor == 0)
                continue;

            if (value % divisor == 0)
            {
                has_divisor = true;
                break;
            }
        }

        if (!has_divisor)
        {
            if (found)
                std::cout << ' ';

            std::cout << value;
            found = true;
        }
    }

    if (!found)
        std::cout << "NONE";

    std::cout << '\n';

    array_delete(arr);

    return 0;
}