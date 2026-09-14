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
        array_set(arr, i, x);
    }

    return arr;
}

void task1(Array *arr)
{
    size_t n = array_size(arr);

    if (n == 0)
    {
        printf("0\n");
        return;
    }

    Data min = array_get(arr, 0);
    Data max = array_get(arr, 0);

    for (size_t i = 1; i < n; ++i)
    {
        Data x = array_get(arr, i);

        if (x < min)
            min = x;

        if (x > max)
            max = x;
    }

    double average = ((double)min + (double)max) / 2.0;

    int count = 0;

    for (size_t i = 0; i < n; ++i)
    {
        if ((double)array_get(arr, i) < average)
            count++;
    }

    printf("%d\n", count);

    for (size_t i = 0; i < n; ++i)
    {
        if ((double)array_get(arr, i) < average)
            printf("%zu ", i + 1);
    }

    printf("\n");
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    FILE *input = fopen(argv[1], "r");

    if (input == NULL)
        return 1;

    Array *arr = array_create_and_read(input);

    task1(arr);

    array_delete(arr);
    fclose(input);

    return 0;
}
