#include <stdlib.h>
#include "array.h"

typedef struct Array {
    Data* data;
    size_t size;
    FFree* free_fn;
} Array;

Array* array_create(size_t size, FFree f)
{
    Array* arr = (Array*)malloc(sizeof(Array));
    if (!arr) return NULL;

    arr->size = size;
    arr->free_fn = f;
    arr->data = (size > 0) ? (Data*)malloc(sizeof(Data) * size) : NULL;

    if (size > 0 && !arr->data) {
        free(arr);
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        arr->data[i] = (Data)0;
    }

    return arr;
}

void array_delete(Array* arr)
{
    if (!arr) return;

    if (arr->free_fn && arr->data) {
        for (size_t i = 0; i < arr->size; ++i) {
            if (arr->data[i]) {
                arr->free_fn((void*)arr->data[i]);
            }
        }
    }

    free(arr->data);
    free(arr);
}

Data array_get(const Array* arr, size_t index)
{
    if (arr && index < arr->size) {
        return arr->data[index];
    }
    return (Data)0;
}

void array_set(Array* arr, size_t index, Data value)
{
    if (arr && index < arr->size) {
        arr->data[index] = value;
    }
}

size_t array_size(const Array* arr)
{
    return arr ? arr->size : 0;
}
