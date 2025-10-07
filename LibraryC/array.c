#include <stdlib.h>
#include "array.h"

typedef struct Array {
    Data* data;       
    size_t size;      
} Array;

// create array
Array* array_create(size_t size, void* unused)
{
    (void)unused; 
    Array* arr = malloc(sizeof(Array));
    if (!arr) return NULL;

    arr->data = malloc(sizeof(Data) * size);
    if (!arr->data) {
        free(arr);
        return NULL;
    }

    arr->size = size;

    for (size_t i = 0; i < size; ++i) {
        arr->data[i] = 0;
    }

    return arr;
}

// delete array, free memory
void array_delete(Array* arr)
{
    if (!arr) return;

    free(arr->data);
    free(arr);
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    if (!arr || index >= arr->size) return 0;
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    if (!arr || index >= arr->size) return;
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array* arr)
{
    if (!arr) return 0;
    return arr->size;
}
