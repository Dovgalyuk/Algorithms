#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void task1(Array* arr, size_t size)
{
    for (size_t index = 0; index < array_size(arr); index++)
    {
        array_set(arr, index, rand() % 100);
    }

    int sum = 0;
    for (size_t index = 0; index < array_size(arr); index++)
    {
        int num = array_get(arr, index);
        if (num % 2 == 0 && num > 0)
        {
            sum += num;
        }
    }

    printf("sum of even number %d\n", sum);
}

void task2(Array* arr, size_t size)
{
    for (size_t index = 0; index < array_size(arr); index++)
    {
        array_set(arr, index, rand() % 100);
    }

    int count = 0;
    float sum = 0;

    for (size_t index = 0; index < array_size(arr); index++)
    {
        sum += array_get(arr, index);
    }

    float average = sum / array_size(arr);

    printf("Array elements whose value is less than the arithmetic mean:");
    for (size_t index = 0; index < array_size(arr); index++)
    {
        if (array_get(arr, index) < average)
        {
            printf("%d ", array_get(arr, index));
            count++;
        }
    }
    printf("\n");
}

int main() {
    size_t size;

    scanf("%zu", &size);

    Array *arr1 = array_create(size);
    task1(arr1, size);
    array_delete(arr1);

    Array *arr2 = array_create(size);
    task2(arr2, size);
    array_delete(arr2);

    return 0;
}