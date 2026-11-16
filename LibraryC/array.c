#include <stdlib.h>
#include "array.h"

struct Array {
    size_t size;
    Data *items;
    FFree *release;
};

Array *array_create(size_t size, FFree f)
{
    Array *arr = malloc(sizeof(*arr));
    if (!arr)
        return NULL;

    arr->items = calloc(size, sizeof(Data));
    if (size && !arr->items) {
        free(arr);
        return NULL;
    }
    arr->size = size;
    arr->release = f;
    return arr;
}

void array_delete(Array *arr)
{
    if (!arr)
        return;
    if (arr->release) {
        for (size_t i = 0; i < arr->size; ++i) {
            if (arr->items[i])
                arr->release((void *)arr->items[i]);
        }
    }
    free(arr->items);
    free(arr);
}

Data array_get(const Array *arr, size_t index)
{
    return arr->items[index];
}

void array_set(Array *arr, size_t index, Data value)
{
    if (arr->release && arr->items[index] && arr->items[index] != value)
        arr->release((void *)arr->items[index]);
    arr->items[index] = value;
}

size_t array_size(const Array *arr)
{
    return arr->size;
}
