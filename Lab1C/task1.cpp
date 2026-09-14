#include <iostream>
#include <fstream>
#include "array.h"

Array* array_create_and_read(std::ifstream& input)
{
    int n;
    if (input >> n)
    {
        Array* arr = array_create(n);
        for (int i = 0; i < n; ++i)
        {
            int x;
            if (input >> x)
            {
                array_set(arr, i, x);
            }
        }
        return arr;
    }
    return nullptr;
}

void task1(Array* arr)
{
    if (!arr) return;
    size_t n = array_size(arr);
    int max_i = 0, min_i = 0;
    int sum = 0;
    for (int i = 1;i < n;i++) {
        if (array_get(arr, max_i) < array_get(arr, i))
            max_i = i;
        if (array_get(arr, min_i) > array_get(arr, i))
            min_i = i;
    }
    if (min_i > max_i) {
        for (int i = max_i + 1; i < min_i;i++) {
            sum += array_get(arr, i);
        }
    }
    else {
        for (int i = min_i + 1; i < max_i;i++) {
            sum += array_get(arr, i);
        }
    }
    std::cout << sum;
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        return 1;
    }

    Array* arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    input.close();
    return 0;
}