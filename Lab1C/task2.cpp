#include <fstream>
#include <iostream>

#include "array.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    std::ifstream input(argv[1]);

    if (!input)
    {
        return 1;
    }

    int n;
    input >> n;

    Array* arr = array_create(n);

    for (int i = 0; i < n; ++i)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }


    int frequency[1001] = {};


    // считаем количество повторений каждого элемента
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int value = static_cast<int>(array_get(arr, i));

        if (value >= 0 && value <= 1000)
        {
            frequency[value]++;
        }
    }


    bool printed[1001] = {};


    // выводим элементы, которые встречаются ровно два раза
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int value = static_cast<int>(array_get(arr, i));

        if (value >= 0 && value <= 1000)
        {
            if (frequency[value] == 2 && !printed[value])
            {
                std::cout << value << ' ';
                printed[value] = true;
            }
        }
    }


    std::cout << '\n';


    array_delete(arr);

    return 0;
}