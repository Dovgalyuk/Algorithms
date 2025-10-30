#include "array.h"
#include <stdlib.h>

Array* array_create(size_t size) {
    Array* arr = (Array*)malloc(sizeof(Array));
    if (!arr) return NULL;
    
    arr->data = (int*)malloc(size * sizeof(int));
    if (!arr->data) {
        free(arr);
        return NULL;
    }
    
    arr->size = size;
    return arr;
}

void array_destroy(Array* arr) {
    if (arr) {
        free(arr->data);
        free(arr);
    }
}

int array_get(Array* arr, size_t index) {
    if (index >= arr->size) return 0;
    return arr->data[index];
}

void array_set(Array* arr, size_t index, int value) {
    if (index < arr->size) {
        arr->data[index] = value;
    }
}

size_t array_size(Array* arr) {
    return arr->size;
}