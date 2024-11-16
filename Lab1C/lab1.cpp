#include <stdio.h>
#include <iostream>
#include <fstream>

#include "array.h"

Array *array_create_and_read(std::ifstream &input)
{
    size_t array_size;
    input >> array_size;

    Array *arr = array_create((size_t)array_size);

    int number = 0;
    size_t index = 0;
    while (input >> number)
    {
        array_set(arr, index, number);
        index++;

        if (index == array_size)
            break;
    }

    return arr;
}

void task1(Array *arr)
{
    int current_number = 0;
    int sum_of_number_digits = 0;
    int sum_of_numbers_digits = 0;

    for (size_t i = 0; i < array_size(arr); i++)
    {
        current_number = array_get(arr, i);

        while (current_number > 0)
        {
            sum_of_number_digits += current_number % 10;
            current_number /= 10;
        }
        sum_of_numbers_digits += sum_of_number_digits;
        sum_of_number_digits = 0;
    }

    std::cout << "task_1: " << sum_of_numbers_digits << std::endl;
}

void task2(Array *arr)
{
    int sum = 0;
    size_t min_index = 0;
    size_t max_index = 0;

   for (size_t index = 0; index < array_size(arr); index++)
   {
        if (array_get(arr, index) > array_get(arr, max_index))
        {
            max_index = index;
        }

        if (array_get(arr, index) < array_get(arr, min_index))
        {
            min_index = index;
        }
    }

    if (min_index > max_index)
    {
        std::swap(min_index, max_index);
    }

    for (size_t index = min_index + 1; index < max_index; index++)
    {
        sum += array_get(arr, index);
    }

    std::cout << "task_2: " << sum;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "args error" << std::endl;
        return 1;
    }

    Array *arr = nullptr;
    std::ifstream input(argv[1]);

    if (!input)
    {
        std::cerr << "read file error " << argv[1] << std::endl;
        return 1;
    }
    

    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    input.close();
}
