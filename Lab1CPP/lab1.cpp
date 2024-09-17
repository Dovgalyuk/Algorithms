#include <stdio.h>
#include "array.h"
#include <fstream>
#include <iostream>

Array* array_create_and_read(std::ifstream& input)
{
    size_t num;

    if (!(input >> num))
    {
        throw std::invalid_argument("Failed to read array size");
    }

    Array* arr = array_create(num);

    for (size_t i = 0; i < num; ++i)
    {
        int x;
        if (!(input >> x))
        {
            array_delete(arr);
            throw std::invalid_argument("Failed to read number");
        }
        array_set(arr, i, x);
    }
    return arr;
}

void array_print(Array* arr)
{
    for (size_t i = 0; i < array_size(arr); i++)
    {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;
}

void task1(std::ifstream& input)
{
    Array* arr = array_create_and_read(input);

    int m;
    int n;
    if (!(input >> m) || !(input >> n))
    {
        throw std::invalid_argument("The number is incorrect");
    }

    for (size_t i = 0; i < array_size(arr); i++)
    {
        int value = array_get(arr, i);
        if (value % 2 != 0)
        {
            int val = value - m;
            array_set(arr, i, val);
        }
    }

    for (size_t i = 1; i < array_size(arr); i += 2)
    {
        int value = array_get(arr, i);
        int val = value + n;
        array_set(arr, i, val);
    }

    array_print(arr);
    array_delete(arr);
}

void task2(std::ifstream& input)
{
    Array* arr = array_create_and_read(input);

    int a;
    int b;

    if (!(input >> a) || !(input >> b))
    {
        throw std::invalid_argument("The number is incorrect");
    }

    size_t index = 0;
    for (size_t i = 0; i < array_size(arr); i++)
    {
        int numberArray = array_get(arr, i);
        if (numberArray < a || numberArray > b)
        {
            array_set(arr, index++, array_get(arr, i));
        }
    }

    while (index < array_size(arr))
    {
        array_set(arr, index++, 0);
    }

    array_print(arr);
    array_delete(arr);
}

int main()
{
    std::ifstream input("input.txt");
    if (input.is_open())
    {
        task1(input);

        task2(input);
    }
    input.close();
    return 0;
}