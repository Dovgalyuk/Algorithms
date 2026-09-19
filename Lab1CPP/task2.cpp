#include <iostream>
#include <fstream>
#include <cstdlib>   // std::abs для int

#include "array.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: task2 <input_file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);

    if (!input)
    {
        std::cerr << "Cannot open input file\n";
        return 1;
    }

    std::size_t n;

    if (!(input >> n))
    {
        std::cerr << "Invalid input\n";
        return 1;
    }

    Array* arr = array_create(n);
    if (!arr)
    {
        std::cerr << "Cannot allocate array\n";
        return 1;
    }

    // Читаем n чисел из файла
    for (std::size_t i = 0; i < n; ++i)
    {
        int value;
        if (!(input >> value))
        {
            std::cerr << "Invalid input: expected " << n << " numbers\n";
            array_delete(&arr);
            return 1;
        }
        array_set(arr, i, value);
    }

    // Ищем минимальную разность между РАЗЛИЧНЫМИ по значению
    // чётными элементами массива.
    int best = -1; // -1 означает "ещё не найдено"

    for (std::size_t i = 0; i < n; ++i)
    {
        int a = array_get(arr, i);

        if (a % 2 != 0)
            continue;

        for (std::size_t j = i + 1; j < n; ++j)
        {
            int b = array_get(arr, j);

            if (b % 2 != 0)
                continue;

            if (a == b)          // игнорируем одинаковые значения
                continue;

            int diff = std::abs(a - b);

            if (best == -1 || diff < best)
                best = diff;
        }
    }

    if (best == -1)
    {
        std::cerr << "No suitable even elements found\n";
        array_delete(&arr);
        return 1;
    }

    std::cout << best << '\n';

    array_delete(&arr);
    return 0;
}