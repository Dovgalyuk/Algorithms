#include <stdio.h>
#include <stdlib.h>
#include "array.h"

typedef struct Array
{
    size_t size;
    Data *value;
} Array;

// create array
Array *array_create(size_t size, FFree f)
{
    Array *result = malloc(sizeof(Array)); 
    if (result == NULL) {
        return NULL;
    }
    result->size = size;
    result->value = malloc(sizeof(Data) * size);
    if (result->value == NULL) {
        free(result);
        return NULL;
    }
    return result;
}

// delete array, free memory
void array_delete(Array *arr)
{
    free(arr->value);
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (index < arr->size) {
        return arr->value[index];
    } else {
        fprintf(stderr, "Error: index %zu is out of bounds\n", index);
        exit(1);
    }
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index < arr->size) { 
        arr->value[index] = value;
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