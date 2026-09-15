
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "array.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: Lab1CPP <input_file>\n";
        return 1;
    }

    // Открываем входной файл
    std::ifstream input(argv[1]);

    if (!input)
    {
        std::cerr << "Cannot open input file\n";
        return 1;
    }


    size_t n;

    if (!(input >> n))
    {
        std::cerr << "Cannot read array size\n";
        return 1;
    }


    Array* arr = array_create(n);

    for (size_t i = 0; i < n; ++i)
    {
        int value;

        if (!(input >> value))
        {
            std::cerr << "Not enough input data\n";
            array_delete(arr);
            return 1;
        }

        array_set(arr, i, value);
    }

    size_t even_count = 0;

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        if (array_get(arr, i) % 2 == 0)
        {
            ++even_count;
        }
    }


    Array* even_indices = array_create(even_count);

    size_t index = 0;

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        if (array_get(arr, i) % 2 == 0)
        {
            array_set(even_indices, index, static_cast<int>(i));
            ++index;
        }
    }


    std::cout << "Even indices: ";

    for (size_t i = 0; i < array_size(even_indices); ++i)
    {
        if (i > 0)
        {
            std::cout << ' ';
        }

        std::cout << array_get(even_indices, i);
    }

    std::cout << '\n';

    array_delete(even_indices);




    int count[1001] = {};


    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int value = array_get(arr, i);

        if (value < 0 || value > 1000)
        {
            std::cerr << "Value must be in range 0..1000\n";
            array_delete(arr);
            return 1;
        }

        ++count[value];
    }


    std::cout << "Unique elements: ";

    bool first = true;

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int value = array_get(arr, i);

        if (count[value] == 1)
        {
            if (!first)
            {
                std::cout << ' ';
            }

            std::cout << value;
            first = false;
        }
    }

    std::cout << '\n';



    array_delete(arr);

    return 0;
}

