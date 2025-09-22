#include <stdio.h>
#include "array.h"

Array* array_create_and_read(FILE* input)
{
    int n;
    if (fscanf(input, "%d", &n) != 1 || n <= 0)
    {
        return NULL;
    }

    Array* arr = array_create(n, NULL);

    for (int i = 0; i < n; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }

    return arr;
}

void task1(Array* arr)
{
    if (arr == NULL || array_size(arr) == 0)
    {
        return;
    }

    int count = 0;
    for (size_t i = 0; i < array_size(arr); i++)
    {
        int value = (int) array_get(arr, i);
        for (int j = 2; j < 10; j++)
        {
            if (value % j == 0)
            {
                count++;
                break;
            }
        }
    }

    printf("%d\n", count);
}

void task2(Array* arr)
{
    if (arr == NULL || array_size(arr) == 0)
    {
        return;
    }

    int max_count = 0;
    int most_frequent = (int) array_get(arr, 0);

    for (size_t i = 0; i < array_size(arr); i++)
    {
        int current_count = 0;
        for (size_t j = 0; j < array_size(arr); j++)
        {
            if (array_get(arr, i) == array_get(arr, j))
            {
                current_count++;
            }
        }

        if (current_count > max_count)
        {
            max_count = current_count;
            most_frequent = (int) array_get(arr, i);
        }
    }

    printf("%d", most_frequent);
}

int main(int argc, char** argv)
{
    Array* arr = NULL;
    FILE* input = fopen(argv[1], "r");

    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    fclose(input);
}
