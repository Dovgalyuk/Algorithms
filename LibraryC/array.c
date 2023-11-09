#include <stdio.h>
#include <stdlib.h>
#include "array.h"

typedef struct Array
{
    size_t size;
    Data value;
} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    Array *result = malloc(sizeof(Array) * size); 
    if (result == NULL) {
        return NULL;
    }
    result->size = size;
    //result->FFreef = f; 
    return result;
}

// delete array, free memory
void array_delete(Array *arr, FFree f)
{
    for (size_t i = 0; i < arr->size; i++) {
        f(arr[i].value);
    }
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (index < arr->size) {
        return arr[index].value;
    } else {
        fprintf(stderr, "Error: index %zu is out of bounds\n", index);
        exit(1);
    }
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index < arr->size) { 
        arr[index].value = value;
    } else {
        fprintf(stderr, "Error: index %zu is out of bounds\n", index);
        exit(1);
    }
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
