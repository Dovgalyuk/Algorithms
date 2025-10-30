#include "array.h"
#include <stdlib.h>

Array* array_create(int size, int* data) {
    Array* arr = (Array*)malloc(sizeof(Array));
    arr->size = size;
    arr->data = (int*)malloc(size * sizeof(int));
    if (data) {
        for (int i = 0; i < size; i++) {
            arr->data[i] = data[i];
        }
    }
    return arr;
}

void array_set(Array* arr, int index, int value) {
    if (arr && index >= 0 && index < arr->size) {
        arr->data[index] = value;
    }
}

int array_get(Array* arr, int index) {
    if (arr && index >= 0 && index < arr->size) {
        return arr->data[index];
    }
    return 0;
}

void array_delete(Array* arr) {
    if (arr) {
        free(arr->data);
        free(arr);
    }
}