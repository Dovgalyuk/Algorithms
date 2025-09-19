#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

struct Array {
	Data *data;
	size_t size;
	FFree *free_func;
};

Array* array_create(size_t size, FFree *f){
    Array* arr = malloc(sizeof(Array));
    if (!arr) return NULL;
    arr->size = size;
    arr->free_func = f;
    arr->data = size ? calloc(size, sizeof(Data)) : NULL;
    if (size && !arr->data) { 
        free(arr); return NULL; 
    }
    return arr;
}

size_t array_size(const Array* arr) {
    if (arr == NULL) return 0;
    return arr->size;
}

Data array_get(const Array* arr, size_t index) {
    if (arr == NULL || index >= arr->size) {
       return 0;
    }
    return arr->data[index];
}

void array_delete(Array* arr) {
    if (!arr) return;
    if (arr->free_func && arr->data) {
        for (size_t i = 0; i < arr->size; ++i) {
            if (arr->data[i]) arr->free_func((void*)arr->data[i]);
        }
    }
    free(arr->data);
    free(arr);
}

void array_set(Array *arr, size_t index, Data value) {
	if (!arr || index >= arr->size) return;
	if (arr->free_func && arr->data[index] && arr->data[index] != value)
		arr->free_func((void*)arr->data[index]);
	arr->data[index] = value;
}