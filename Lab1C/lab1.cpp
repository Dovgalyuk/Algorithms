#include <stdio.h>
#include "array.h"
#include "tasks.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);
    /* Create array */
    Array *arr = array_create((size_t)n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

int main(int argc, char **argv)
{
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    
    int shift;
    if (fscanf(input, "%d", &shift) != 1) {
        fclose(input);
        return 1;
    }

    arr = array_create_and_read(input);
    task2(arr, shift);
    array_delete(arr);
    fclose(input);
    return 0;
}
