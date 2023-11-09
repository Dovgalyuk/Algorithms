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
    for (size_t i = 0; i < size; ++i) {
        result->value[i] = NULL;
    }
    return result;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr != NULL) {
        for (size_t i = 0; i < arr->size; ++i) {
            if (arr->value[i] != NULL) {
                free(arr->value[i]);
            }
        }
        free(arr->value);
        free(arr);
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (arr == NULL) {
        fprintf(stderr, "Error: array is NULL\n");
        exit(1);
    }
    if (index >= arr->size) {
        fprintf(stderr, "Error: index %zu is out of bounds\n", index);
        exit(1);
    }
    return arr->value[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (arr == NULL) {
        fprintf(stderr, "Error: array is NULL\n");
        exit(1);
    }
    if (index >= arr->size) {
        fprintf(stderr, "Error: index %zu is out of bounds\n", index);
        exit(1);
    }
    arr->value[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    if (arr == NULL) {
        fprintf(stderr, "Error: array is NULL\n");
        exit(1);
    }
    return arr->size;
}
