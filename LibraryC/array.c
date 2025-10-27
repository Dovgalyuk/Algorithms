#include <stdlib.h>
#include "array.h"
#include <stdio.h>

typedef struct Array {
    size_t size;
    Data *data;
    FFree *freefunc;
} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    Array *arr = (Array*)malloc(sizeof(Array));
    if (!arr) return NULL;
    arr->size = size;
    arr->freefunc = f;
    if (size > 0){
        arr->data = (Data*)calloc(size, sizeof(Data));
        if(!arr->data){
            free(arr);
            return NULL;
        }

    }
    else{
        arr->data = NULL;
    }
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (!arr) return;

    if(arr->freefunc){
        for (size_t i = 0; i < arr->size; i++){
            if (arr->data[i] != 0) {
                arr->freefunc((void*)(uintptr_t)arr->data[i]);
            }
        }
    }
    free(arr->data);
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (arr == NULL){
        fprintf(stderr, "array_get: arr is NULL\n");
        return (Data)0;
    }
    if (index >= arr->size){
        fprintf(stderr, "array_get: index %zu out of bounds (size=%zu)\n", index, arr->size);
        return (Data)0;
    }
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (arr == NULL){
        fprintf(stderr, "array_set: arr is NULL\n");
        return;
    }
    if (index >= arr->size){
        fprintf(stderr, "array_set: index %zu out of bounds (size=%zu)\n", index, arr->size);
        return;
    }
    if (arr->freefunc && arr->data[index] != 0) {
        arr->freefunc((void*)(uintptr_t)arr->data[index]);
    }
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    if (arr == NULL){
        fprintf(stderr, "array_size: arr is NULL\n");
        return 0;
    }
    return arr->size;
}
