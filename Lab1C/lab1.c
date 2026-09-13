#include <stdio.h>
#include "array.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);
    
    Array *arr = array_create(n, NULL);
    
    for (int i = 0 ; i < n ; ++i)
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
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");

    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    /* Create another array here */
    arr = array_create_and_read(input);

    size_t a, b;
    fscanf(input, "%zu %zu", &a, &b);

    task2(arr, (Data)a, (Data)b);

    array_delete(arr);
    fclose(input);
}
