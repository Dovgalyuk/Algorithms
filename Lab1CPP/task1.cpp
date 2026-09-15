#include <iostream>
#include <fstream>

#include "array.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: task1 <input_file>\n";
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
    Array* crossed = array_create(n);

    // Заполняем массив натуральными числами
    // 1, 2, 3, ..., n
    for (std::size_t i = 0; i < n; ++i)
    {
        array_set(arr, i, static_cast<int>(i + 1));
        array_set(crossed, i, 0);
    }

    if (n > 0)
        array_set(crossed, 0, 1); // 1 не является простым

    // Решето Эратосфена
    for (std::size_t p = 2; p * p <= n; ++p)
    {
        if (array_get(crossed, p - 1) == 0)
        {
            for (std::size_t multiple = p * p;
                 multiple <= n;
                 multiple += p)
            {
                array_set(crossed, multiple - 1, 1);
            }
        }
    }

    // Переносим простые числа в начало
    std::size_t writeIndex = 0;

    for (std::size_t i = 0; i < n; ++i)
    {
        if (array_get(crossed, i) == 0)
        {
            array_set(
                arr,
                writeIndex,
                array_get(arr, i)
            );

            ++writeIndex;
        }
    }

    // Оставшиеся элементы заполняем нулями
    while (writeIndex < n)
    {
        array_set(arr, writeIndex, 0);
        ++writeIndex;
    }

    // Вывод массива
    for (std::size_t i = 0; i < n; ++i)
    {
        if (i > 0)
            std::cout << ' ';

        std::cout << array_get(arr, i);
    }

    std::cout << '\n';

    array_delete(&crossed);
    array_delete(&arr);

    return 0;
}