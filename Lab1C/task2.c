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

void task2(Array *arr, Data a, Data b)
{
    size_t n = array_size(arr);
    size_t write = 0;

    for (size_t i = 0; i < n; ++i)
    {
        Data x = array_get(arr, i);

        if (x < a || x > b)
        {
            array_set(arr, write, x);
            write++;
        }
    }

    while (write < n)
    {
        array_set(arr, write, 0);
        write++;
    }

    for (size_t i = 0; i < n; ++i)
    {
        printf("%zu ", (size_t)array_get(arr, i));
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

    size_t a, b;
    fscanf(input, "%zu %zu", &a, &b);

    task2(arr, (Data)a, (Data)b);

    array_delete(arr);
    fclose(input);

    return 0;
}
