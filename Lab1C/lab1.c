#include <stdio.h>
#include "array.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);
    Array *arr = array_create(n, NULL);
    for (int i = 0; i < n; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, (Data)x);
    }
    return arr;
}

void task1(Array *arr)
{
    int positive = 0, negative = 0, zero = 0;
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int value = (int)array_get(arr, i);
        if (value > 0)
            positive++;
        else if (value < 0)
            negative++;
        else
            zero++;
    }

    printf("Array elements:\n");
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        printf("%d ", (int)array_get(arr, i));
    }
    printf("\nPositive: %d, Negative: %d, Zero: %d\n", positive, negative, zero);
}

void task2(Array *arr)
{
    int min_diff = __INT_MAX__;
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int value1 = (int)array_get(arr, i);
        if (value1 % 2 != 0)
            continue;
        for (size_t j = i + 1; j < array_size(arr); ++j)
        {
            int value2 = (int)array_get(arr, j);
            if (value2 % 2 != 0)
                continue;
            int diff = value1 - value2;
            if (diff < 0)
                diff = -diff;
            if (diff < min_diff)
                min_diff = diff;
        }
    }
    printf("Minimum difference between different even elements: %d\n", min_diff);
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        perror("Failed to open input file");
        return 1;
    }

    Array *arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    rewind(input);
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    fclose(input);
    return 0;
}
