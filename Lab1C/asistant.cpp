#include "asistant.h"

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