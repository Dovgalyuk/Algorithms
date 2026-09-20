// Читает из файла размер массива и его элементы (числа от 0 до 1000),
// находит значение, которое встречается чаще всего. Время работы O(N).

#include <fstream>
#include <iostream>

#include "array.h"

// Максимальное значение элемента по условию задачи
const Data MAX_VALUE = 1000;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: Lab1CPPFrequency <input file>\n";
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
        if (value < 0 || value > MAX_VALUE)
        {
            std::cerr << "Value " << value << " is out of range [0, 1000]\n";
            return 1;
        }
        arr.set(i, value);
    }

    if (size == 0)
    {
        std::cout << "Array is empty\n";
        return 0;
    }

    // counts[v] - сколько раз встретилось значение v.
    // Массив создаётся заполненным нулями.
    Array counts(static_cast<size_t>(MAX_VALUE) + 1);

    // Один проход по данным: O(N)
    for (size_t i = 0; i < arr.size(); ++i)
    {
        const size_t value = static_cast<size_t>(arr.get(i));
        counts.set(value, counts.get(value) + 1);
    }

    // Один проход по счётчикам: ровно 1001 шаг, от N не зависит.
    // При равном количестве побеждает меньшее значение.
    Data best_value = 0;
    Data best_count = 0;
    for (size_t value = 0; value < counts.size(); ++value)
    {
        if (counts.get(value) > best_count)
        {
            best_count = counts.get(value);
            best_value = static_cast<Data>(value);
        }
    }

    std::cout << "Most frequent value: " << best_value
        << ", count: " << best_count << "\n";
    return 0;
}