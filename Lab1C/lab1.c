#include <stdio.h>
#include "array.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    if (fscanf(input, "%d", &n) != 1)
        n = 0;
    /* Create array */
    Array *arr = array_create(n, NULL);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) != 1)
            x = 0;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    int n = (int)array_size(arr);
    for (int i = 0 ; i < n ; ++i)
    {
        printf("%d", (int)array_get(arr, i));
        if (i + 1 < n)
            printf(" ");
    }
    printf("\n");
}

void task2(Array *arr)
{
    int n = (int)array_size(arr);
    for (int i = 0 ; i < n ; ++i)
    {
        printf("%d", (int)array_get(arr, i));
        if (i + 1 < n)
            printf(" ");
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
    task2(arr);
    array_delete(arr);
    fclose(input);
}
