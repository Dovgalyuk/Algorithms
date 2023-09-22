#include <stdio.h>
#include <ctime>
#include <iostream>

#include "array.h"

void task1(Array* arr)
{
    size_t result = 0;

    for (size_t i = 0; i < array_size(arr); i++)
    {
        array_set(arr, i, rand());
        
        if (i % 2 == 0)
            result += array_get(arr, i);
        else
            result -= array_get(arr, i);
    }

    std::cout << "Task 1: " << result << std::endl;
}

void task2(Array* arr)
{
    bool flag = true;

    for (size_t i = 0; i < array_size(arr); i++)
        array_set(arr, i, rand());

    std::cout << "Task 2: ";

    for (size_t i = 0; i < array_size(arr); i++)
    {
        for (size_t j = 0; j < array_size(arr); j++)
        {
            if (array_get(arr, i) == array_get(arr, j) && i != j)
                flag = false;
        }

        if (flag)
            std::cout << array_get(arr, i) << " ";
        else
            flag = true;
    }
}

int main()
{
    srand(time(NULL) / 1000);

    Array* arr = NULL;
    size_t size;

    /* Create array here */
    std::cout << "Enter size of array: ";
    std::cin >> size;

    arr = array_create(size);
    task1(arr);
    array_delete(arr);

    /* Create another array here */
    std::cout << std::endl << "Enter size of array: ";
    std::cin >> size;

    arr = array_create(size);
    task2(arr);
    array_delete(arr);
}