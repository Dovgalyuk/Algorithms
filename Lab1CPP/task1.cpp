#include <iostream>
#include <fstream>
#include <string>
#include "array.h"

Array<int> *array_create_and_read(std::ifstream &input)
{
    size_t n;

    if (input >> n)
    {
        Array<int> *arr = new Array<int>(n);

        for (size_t i = 0; i < n; ++i)
        {
            int x;

            if (input >> x)
            {
                arr->set(i, x);
            }
        }
        return arr;
    }
    return nullptr;
}

void task1(Array<int> *arr)
{
    size_t size_arr = arr->size();
    long long multiply = 1;

    for (size_t i = 0; i < size_arr; i++)
    {
        multiply *= arr->get(i);
    }

    if (multiply == 0)
    {
        std::cout << "0";
        return;
    }

    long long sum = 0;

    for (size_t i = 0; i < size_arr; i++)
    {
        int x = arr->get(i);

        if (x == 0)
        {
            std::cout << "0";
            return;
        }
        sum += multiply / arr->get(i);
    }

    if (sum == 0)
    {
        std::cout << "0";
        return;
    }
    std::cout << multiply * 1.f / sum << " ";
}

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3)
    {
        return 1;
    }

    Array<int> *arr;

    std::ifstream input(argv[1]);

    arr = array_create_and_read(input);

    if (arr != nullptr)
    {
        task1(arr);
        delete arr;
    }

    input.close();
}