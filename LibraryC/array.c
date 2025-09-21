#include <stdlib.h>
#include <string.h>
#include "array.h"

typedef struct Array {
    size_t size;
    Data* data;
    FFree* free_func;
} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    Array* arr = malloc(sizeof(Array));
    if (arr == NULL) {
        return NULL;
    }
    
    arr->size = size;
    arr->free_func = f;
    arr->data = malloc(size * sizeof(Data));
    
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }
    
    // Инициализируем нулями
    memset(arr->data, 0, size * sizeof(Data));
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr == NULL) return;
    
    if (arr->free_func != NULL) {
        for (size_t i = 0; i < arr->size; i++) {
            if (arr->data[i] != 0) {
                arr->free_func((void*)arr->data[i]);
            }
        }
    }
    
    free(arr->data);
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (arr == NULL || index >= arr->size) {
        return (Data)0;
    }
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (arr == NULL || index >= arr->size) {
        return;
    }
    
    if (arr->free_func != NULL && arr->data[index] != 0) {
        arr->free_func((void*)arr->data[index]);
    }
    
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    if (arr == NULL) {
        return 0;
    }
    return arr->size;
}
