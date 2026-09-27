#include <fstream>
#include <iostream>
#include "../Library/array.h"

const int MAX_VALUE = 1000;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Использование: most_frequent <входной файл>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cerr << "Не удалось открыть файл " << argv[1] << std::endl;
        return 1;
    }

    size_t count = 0;
    input >> count;

    Array* arr = array_create(count);
    for (size_t i = 0; i < count; i++)
    {
        Data value = 0;
        input >> value;
        array_set(arr, i, value);
    }
    input.close();

    int counters[MAX_VALUE + 1] = { 0 };
    for (size_t i = 0; i < array_size(arr); i++)
    {
        Data value = array_get(arr, i);
        counters[value]++;
    }

    Data mostFrequent = 0;
    int bestCount = -1;
    for (int value = 0; value <= MAX_VALUE; value++)
    {
        if (counters[value] > bestCount)
        {
            bestCount = counters[value];
            mostFrequent = value;
        }
    }

    array_destroy(arr);

    std::cout << mostFrequent << std::endl;
    return 0;
}
