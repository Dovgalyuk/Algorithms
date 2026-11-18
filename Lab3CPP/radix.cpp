// Читает из файла последовательность положительных чисел
// и сортирует её поразрядной сортировкой с помощью очередей.

#include <fstream>
#include <iostream>

#include "queue.h"

// Сколько битов числа рассматривается за один проход
const int BITS = 2;

const int BUCKETS = 1 << BITS;

const Data MASK = BUCKETS - 1;

// Сортирует числа в очереди по возрастанию.
static void radix_sort(Queue& numbers, Data max_value)
{
    Queue buckets[BUCKETS];

    int shift = 0;
    for (Data rest = max_value; rest > 0; rest >>= BITS)
    {
        // Раскладываем числа по очередям в зависимости от текущих битов
        while (!numbers.empty())
        {
            const Data value = numbers.get();
            numbers.remove();
            buckets[(value >> shift) & MASK].insert(value);
        }

        // собираем числа обратно: сначала из очереди 0, потом 1 и т.д.
        // Очередь сохраняет порядок, поэтому результат прошлых проходов не теряется.
        for (int i = 0; i < BUCKETS; ++i)
        {
            while (!buckets[i].empty())
            {
                numbers.insert(buckets[i].get());
                buckets[i].remove();
            }
        }

        shift += BITS;
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: Lab3CPPRadix <input file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open file " << argv[1] << "\n";
        return 1;
    }

    Queue numbers;
    Data max_value = 0;
    Data value = 0;
    while (input >> value)
    {
        if (value < 0)
        {
            std::cerr << "Value " << value << " is negative\n";
            return 1;
        }
        if (value > max_value)
            max_value = value;
        numbers.insert(value);
    }

    // чтение остановилось не в конце файла - значит, там не число
    if (!input.eof())
    {
        std::cerr << "Cannot read a number from the file\n";
        return 1;
    }

    radix_sort(numbers, max_value);

    // между числами пробел, после последнего - перевод строки
    bool first = true;
    while (!numbers.empty())
    {
        if (!first)
            std::cout << " ";
        std::cout << numbers.get();
        numbers.remove();
        first = false;
    }
    std::cout << "\n";
    return 0;
}