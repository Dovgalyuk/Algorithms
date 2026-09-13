#include <iostream>
#include <fstream>
#include "array.h"

unsigned long long calculateFactorial(int n)
{
    if (n < 0) return 0;
    unsigned long long fact = 1;
    for (int i = 1; i <= n; ++i)
    {
        fact *= i;
    }
    return fact;
}

void taskDivisibility(const Array* arr)
{
    size_t size = array_size(arr);
    std::cout << "Elements not divisible by any other element in array: ";

    bool foundAny = false;
    for (size_t i = 0; i < size; ++i)
    {
        int current = array_get(arr, i);
        bool isDivisible = false;

        for (size_t j = 0; j < size; ++j)
        {
            if (i == j) continue;
            int other = array_get(arr, j);
            if (other != 0 && current % other == 0)
            {
                isDivisible = true;
                break;
            }
        }

        if (!isDivisible)
        {
            std::cout << current << " ";
            foundAny = true;
        }
    }

    if (!foundAny)
    {
        std::cout << "None";
    }
    std::cout << "\n";
}

int main()
{
    std::ifstream input("input.txt");
    if (!input.is_open())
    {
        std::cerr << "Error: Could not open input.txt\n";
        return 1;
    }

    size_t size = 0;
    if (!(input >> size) || size == 0)
    {
        std::cerr << "Error: Invalid array size in input.txt\n";
        return 1;
    }

    Array* arr = array_create(size);
    for (size_t i = 0; i < size; ++i)
    {
        int val = 0;
        if (input >> val)
        {
            array_set(arr, i, val);
        }
    }
    input.close();

    int firstElem = array_get(arr, 0);
    std::cout << "Factorial of first element (" << firstElem << "): "
        << calculateFactorial(firstElem) << "\n";

    taskDivisibility(arr);

    array_delete(arr);
    return 0;
}