#include <iostream>
#include <fstream>
#include "array.h"

Array* array_create_and_read(std::ifstream& input)
{
    int n;
    input >> n;

    Array* arr = array_create(n);
    for (int i = 0; i < n; ++i)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array* arr)
{
    Data max = array_get(arr, 0);
    int n = array_size(arr);
    for (int i = 1; i < n; ++i)
    {
        Data val = array_get(arr, i);
        if (val > max) max = val;
    }

    int first = -1;
    int last = -1;

    for (int i = 0; i < n; ++i)
    {
        if (array_get(arr, i) == max)
        {
            if (first == -1) first = i;
            last = i;
        }
    }

    std::cout << max << " " << first + 1 << " " << last + 1 << "\n";
}

void task2(Array* arr)
{
    bool found_unique = false;
    int n = array_size(arr);

    for (int i = 0; i < n; ++i)
    {
        Data current = array_get(arr, i);
        bool is_unique = true;

        for (int j = 0; j < n; ++j)
        {
            if (i != j && array_get(arr, j) == current)
            {
                is_unique = false;
                break;
            }
        }

        if (is_unique)
        {
            if (found_unique) std::cout << " ";
            std::cout << current;
            found_unique = true;
        }
    }

    if (!found_unique) std::cout << "none";
    std::cout << "\n";
}

int main(int argc, char** argv)
{
    if (argc < 2) return 1;

    std::ifstream input(argv[1]);
    if (!input.is_open()) return 1;

    Array* arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    return 0;
}
