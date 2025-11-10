#include "array.h"
#include <stdio.h>
#include <stdlib.h>

// ОПРЕДЕЛЕНИЕ СТРУКТУРЫ ТОЛЬКО В C-ФАЙЛЕ
struct Array {
    Data* data;
    size_t size;
    FFree* free_fn;
};

Array* array_create(size_t size, FFree f)
{
    Array* arr = (Array*)malloc(sizeof(Array));
    if (!arr) return NULL;
    
    arr->data = (Data*)malloc(size * sizeof(Data));
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    
    arr->size = size;
    arr->free_fn = f;
    return arr;
}

void array_delete(Array* arr)
{
    if (!arr) return;
    
    if (arr->free_fn) {
        for (size_t i = 0; i < arr->size; i++) {
            arr->free_fn((void*)arr->data[i]);
        }
    }
    
    free(arr->data);
    free(arr);
}

Data array_get(const Array* arr, size_t index)
{
    if (!arr || index >= arr->size) {
        printf("Invalid array or index\n");
        return (Data)0;
    }
    return arr->data[index];
}

void array_set(Array* arr, size_t index, Data value)
{
    if (!arr || index >= arr->size) return;
    arr->data[index] = value;
}

size_t array_size(const Array* arr)
{
    return arr ? arr->size : 0;
}
