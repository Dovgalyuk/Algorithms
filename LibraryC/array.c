#include <stdlib.h>
#include <string.h>
#include "array.h"

typedef struct Array {
    size_t size;
    Data *data;
    FFree freeFunc;
} Array;

// create array
Array *array_create(size_t size, FFree f) {
    Array *arr = malloc(sizeof(Array));
    if (!arr) return NULL;

    arr->size = size;
    arr->data = malloc(size * sizeof(Data));
    if (!arr->data) {
        free(arr);
        return NULL;
    }

    arr->freeFunc = f;
    memset(arr->data, 0, size * sizeof(Data));

    return arr;
}

// delete array, free memory
void array_delete(Array *arr) {
    if (arr) {
        if (arr->freeFunc){
            for (size_t i = 0; i < arr->size; i++) {
                if (arr->data[i]) 
                    arr->freeFunc((void*)arr->data[i]);
            }
        free(arr->data);
        free(arr);
        }
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index) {
    if (index >= arr->size) return (Data)0;
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value) {
    if (index < arr->size) arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr) {
    if (!arr) return 0;
    return arr->size; 
}
