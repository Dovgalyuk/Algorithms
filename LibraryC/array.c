#include <stdlib.h>
#include "array.h"

typedef struct Array {
    size_t size;
    Data *d;
    FFree *ff;
} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    Array *arr = (Array*)malloc(sizeof(Array));
    if(!arr){
        return NULL;
    }
    arr->size = size;
    arr->ff = f;
    arr->d = (Data*)calloc(size, sizeof(Data));

    if(!arr->d){
        free(arr);
        return NULL;
    }
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if(!arr) return;
    if(arr->ff){
        for(size_t i = 0; i < arr->size; i++){
            if(arr->d[i] != 0){
                arr->ff((void*)arr->d[i]);
            }
        }
    }
    free(arr->d);
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if(!arr || index >= arr->size){
        return (Data)0;
    }
    return arr->d[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if(!arr || index >= arr->size){
        return;
    }
    if(arr->ff && arr->d[index] != 0){
        arr->ff((void*)arr->d[index]);
    }
    arr->d[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr ? arr->size : 0;
}
