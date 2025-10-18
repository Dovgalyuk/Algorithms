#include <stdlib.h>
#include "array.h"

typedef struct Array {
    Data* d;
    size_t size;
    FFree* freeFunc;
} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    Array *arr = (Array*)malloc(sizeof(Array));
    if (arr == NULL) 
        return NULL;
    arr->size = size;
    arr->freeFunc = f;
    arr->d = (Data*)calloc(size, sizeof(Data));
    if (arr->d == NULL) {
        free(arr);
        return NULL;
    }
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if ( arr == NULL ) 
        return;
    if (arr->d == NULL) {
        free(arr);
        return;
    }
    if (arr->freeFunc != NULL) {
        for (size_t i = 0; i < arr->size; i++) {
            if (arr->d[i] != 0) {
                arr->freeFunc((void*)arr->d[i]);
            }
        }
    }
       
    free(arr->d);
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, const size_t index)
{
    if ( arr == NULL || arr->d == NULL || index >= arr->size) 
        return (Data)0;
 
    return (arr->d[index]);
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (arr == NULL || arr->d == NULL || index >= arr->size) 
        return;
        
    arr->d[index] = value;  
   
}

// returns array size
size_t array_size(const Array *arr)
{
    if ( arr == NULL || arr->d == NULL) 
        return (size_t)0;

    return arr->size;
}