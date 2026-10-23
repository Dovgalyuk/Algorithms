#include <stdlib.h>
#include "array.h"

struct Array {
    Data *data;
    FFree *ffree;
    size_t size;
};

// create array
Array *array_create(size_t size, FFree f)
{
    Array *arr = malloc(sizeof(Array));
    if (!arr) return NULL;
    arr->size = size;
    arr->ffree = f;
    arr->data = calloc(size, sizeof(Data));
    if (!arr->data) { free(arr); return NULL; }
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (!arr) return;
    if (arr->ffree) {
        for (size_t i = 0; i < arr->size; i++) {
            if (arr->data[i]) {
                arr->ffree((void*)arr->data[i]);
            }
        }
    }
    free(arr->data);
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (arr->data[index] && arr->ffree) {
        arr->ffree((void*)arr->data[index]);
    }
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
