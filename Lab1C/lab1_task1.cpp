#include <stdio.h>
#include "array.h"
#include "tasks.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    if (fscanf(input, "%d", &n) != 1)
        return NULL;

    Array *arr = array_create((size_t)n);
    for (int i = 0; i < n; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) != 1)
            break;
        array_set(arr, i, x);
    }
    return arr;
}

int main(int argc, char **argv)
{
    if (argc < 2) return 1;

    FILE *input = fopen(argv[1], "r");
    if (!input) return 1;

    Array *arr = array_create_and_read(input);
    if (!arr) { fclose(input); return 1; }

    task1(arr);
    array_delete(arr);

    fclose(input);
    return 0;
}