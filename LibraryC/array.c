//
// Created by Administrator on 9/22/2025.
//

#include "array.h"
#include <stdlib.h>

Array* array_create(size_t size, FFree f)
{
    Array *arr = malloc(sizeof(Array));
    arr->size = size;
    arr->data = (Data*) calloc(size, sizeof(Data));
    arr->free_func = f;
    return arr;
}

void array_delete(Array *arr)
{
    if (arr)
    {
        if (arr->free_func)
        {
            for (size_t i = 0; i < arr->size; i++)
            {
                if (arr->data[i])
                    arr->free_func((void*) arr->data[i]);
            }
        }

        free(arr->data);
        free(arr);
    }
}

Data array_get(const Array *arr, size_t index)
{
    if (index >= arr->size)
        return 0;
    return arr->data[index];
}

void array_set(Array *arr, size_t index, Data value)
{
    if (index >= arr->size)
        return;

    if (arr->data[index] && arr->free_func)
        arr->free_func((void*) arr->data[index]);

    arr->data[index] = value;
}

size_t array_size(const Array *arr)
{
    return arr->size;
}
