#include "array.h"
#include <stdlib.h>

typedef struct Array
{
    size_t size;
    Data *data;
    FFree *distruct;
} Array;

Array *array_create(size_t size, FFree field)
{
    Array *arr = malloc(sizeof(Array));
    if (arr == NULL) {
        return NULL;
    }

    arr->data = malloc(size * sizeof(Data));
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }

    arr->distruct = field;
    arr->size = size;
    return arr;
}

void array_delete(Array *arr)
{
    if (arr == NULL) {
        return;
    }

    if (arr->distruct != NULL) {
        for (size_t i = 0; i < arr->size; i++) {
            arr->distruct((void*)arr->data[i]);
        }
    }
    free(arr->data);
    free(arr);
}

Data array_get(const Array *arr, size_t index)
{
    return arr->data[index];
}

int array_set(Array *arr, size_t index, Data value)
{
    if (arr == NULL || index >= arr->size) {
        return -1;
    }
    arr->data[index] = value;
    return 0;
}

size_t array_size(const Array *arr)
{
    return arr->size;
}

