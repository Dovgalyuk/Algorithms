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

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int value = array_get(arr, i);
        ++frequency[value];
    }

    bool printed[1001] = {};

    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int value = array_get(arr, i);

        if (frequency[value] == 2 && !printed[value])
        {
            std::cout << value << ' ';
            printed[value] = true;
        }
    }

    std::cout << '\n';

    array_delete(arr);

    return 0;
}