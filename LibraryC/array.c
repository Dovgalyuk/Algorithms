#include <stdlib.h>
#include "array.h"

typedef struct Array {
    size_t size;
    Data *data;
} Array;

// create array
Array *array_create(size_t size, FFree f) {
    (void)f;

    Array* arr = (Array*)malloc(sizeof(Array));
    if (arr == NULL) return NULL;

    arr->size = size;
    arr->data = (Data*)malloc(size * sizeof(Data));
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        arr->data[i] = 0;
    }

    return arr;
}

// delete array, free memory
void array_delete(Array* arr) {
    if (arr == NULL) return;

    free(arr->data);
    free(arr);
}

// returns specified array element
Data array_get(const Array *arr, size_t index) {
    if (arr == NULL || index >= arr->size) {
        return 0;
    }
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value) {
    if (arr == NULL || index >= arr->size) return;
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr) {
    if (arr == NULL) return 0;
    return arr->size;
}
