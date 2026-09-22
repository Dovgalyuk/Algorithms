#include <stdlib.h>
#include "array.h"

typedef struct Array {
    Data *data;
    size_t size;
    FFree *f;
} Array;

Array *array_create(size_t size, FFree *f)
{
    Array *arr = (Array *)malloc(sizeof(Array));
    arr->data = (Data *)malloc(sizeof(Data) * size);
    arr->size = size;
    arr->f = f;
    return arr;
}

void array_delete(Array *arr)
{
    if (arr->f) {
        for (size_t i = 0; i < arr->size; i++)
            arr->f((void *)arr->data[i]);
    }
    free(arr->data);
    free(arr);
}

Data array_get(const Array *arr, size_t index)
{
    return arr->data[index];
}

void array_set(Array *arr, size_t index, Data value)
{
    if (arr->f && arr->data[index])
        arr->f((void *)arr->data[index]);
    arr->data[index] = value;
}

size_t array_size(const Array *arr)
{
    return arr->size;
}
