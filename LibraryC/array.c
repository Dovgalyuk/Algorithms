#include <stdlib.h>

#include "array.h"

// create array
Array *array_create(size_t size, FFree f) {
    Array *arr = (Array *)malloc(sizeof(Array));
    if (!arr) return NULL;

    arr->f = f;
    arr->data = (Data *)malloc(size * sizeof(Data));
    if (!arr->data) {
        free(arr);
        return NULL;
    }

    arr->size = size;
    for (size_t i = 0; i < size; i++) arr->data[i] = (Data)0;

    return arr;
}

// delete array, free memory
void array_delete(Array *arr) {
    if (arr) {
        for (size_t i = 0; i < arr->size; i++) {
            if (arr->f) arr->f(arr->data[i]);
        }
        free(arr->data);
        free(arr);
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index) {
    if (index >= arr->size) return (Data)0;
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value) {
    if (index < arr->size) arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr) { return arr->size; }
