#include "array.h"
#include <stdlib.h>

struct Array {
    size_t size;
    Data *data;
    FFree free_func;
};

Array *array_create(size_t size, FFree f) {
    Array *arr = (Array*)malloc(sizeof(Array));
    if (!arr) {
        return NULL;
    }
    arr->size = size;
    arr->free_func = f;
    arr->data = (Data*)calloc(size, sizeof(Data));
    if (!arr->data && size > 0) {
        free(arr);
        return NULL;
    }
    return arr;
}

void array_delete(Array *arr) {
    if (!arr) {
        return;
    }
    if (arr->free_func) {
        for (size_t i = 0; i < arr->size; ++i) {
            if (arr->data[i]) {
                arr->free_func(arr->data[i]);
            }
        }
    }
    free(arr->data);
    free(arr);
}

Data array_get(const Array *arr, size_t index) {
    if (arr && index < arr->size) {
        return arr->data[index];
    }
    return NULL;
}

void array_set(Array *arr, size_t index, Data value) {
    if (arr && index < arr->size) {
        if (arr->data[index] && arr->free_func) {
            arr->free_func(arr->data[index]);
        }
        arr->data[index] = value;
    }
}

size_t array_size(const Array *arr) {
    return arr ? arr->size : 0;
}
