#include "array.h"
#include <stdio.h>  
#include <stdlib.h>

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

void array_destroy(Array* arr)
{
    if (!arr) return;
    
    if (arr->free_fn) {
        for (size_t i = 0; i < arr->size; i++) {
            arr->free_fn(arr->data[i]);
        }
    }
    
    free(arr->data);
    free(arr);
}

Data array_get(const Array* arr, int index)
{
    if (!arr || index < 0 || index >= arr->size) {
        printf("Данные в массив не введены");
        return (Data)0;  
    }
    return arr->data[index];
}

void array_set(Array* arr, int index, Data value) 
{
    if (!arr || index < 0 || index >= arr->size) return;
    arr->data[index] = value; 
}

size_t array_size(const Array* arr)
{
    return arr ? arr->size : 0;
}