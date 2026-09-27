#include <fstream>
#include <iostream>
#include "../Library/array.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Использование: alt_sum <входной файл>" << std::endl;
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

    long long sum = 0;
    for (size_t i = 0; i < array_size(arr); i++)
    {
        Data value = array_get(arr, i);
        if (i % 2 == 0)
        {
            sum += value;
        }
        else
        {
            sum -= value;
        }
    }

    array_destroy(arr);

    std::cout << sum << std::endl;
    return 0;
}
