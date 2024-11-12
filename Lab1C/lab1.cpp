#include <stdio.h>
#include <iostream>

#include "array.h"

Array* array_create_and_read(FILE* input)
{
    size_t n;
    fscanf(input, "%zu", &n);
    /* Create array */
    Array* arr = array_create(n);
    /* Read array data */
    for (size_t i = 0; i < n; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
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
    size_t left_index = 0;
    size_t right_index = 0;

    for (size_t i = 0; i < array_size(arr); i++)
    {
        if (array_get(arr, i) < array_get(arr, min_index))
        {
            min_index = i;

            if (min_index > max_index)
            {
                right_index = min_index;
                left_index = max_index;
                sum = 0;

                i = left_index;
            }
        }

        if (array_get(arr, i) > array_get(arr, max_index))
        {
            max_index = i;

            if (min_index < max_index)
            {
                right_index = max_index;
                left_index = min_index;
                sum = 0;

                i = left_index;
            }
        }

        if (i > left_index && i < right_index)
            sum += array_get(arr, i);
    }

    std::cout << "task_2: " << sum;
}

int main(int argc, char** argv)
{
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input);
}
