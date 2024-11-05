#include <stdlib.h>
#include <string.h>
#include "array.h"

typedef struct Array {
    size_t size;      // Size of the array
    Data* data;      // Pointer to the data
    FFree freeFunc;  // Free function for user data
} Array;

// create array
Array* array_create(size_t size, FFree f) {
    Array* arr = malloc(sizeof(Array));
    if (!arr) return NULL; // Check for allocation failure

    arr->size = size;
    arr->data = malloc(size * sizeof(Data));
    if (!arr->data) {
        free(arr);
        return NULL; // Check for allocation failure
    }

    arr->freeFunc = f;
    memset(arr->data, 0, size * sizeof(Data)); // Initialize array elements to 0

    return arr;
}

// delete array, free memory
void array_delete(Array* arr) {
    if (arr) {
        if (arr->freeFunc) {
            for (size_t i = 0; i < arr->size; i++) {
                if (arr->data[i]) {
                    arr->freeFunc((void*)arr->data[i]); // Free each element if necessary
                }
            }
        }
        free(arr->data); // Free the data array
        free(arr);       // Free the array struct
    }
}

// returns specified array element
Data array_get(const Array* arr, size_t index) {
    if (arr == NULL) {
        return 1;
    }
    if (index < arr->size) {
        return arr->data[index];
    }
    return (Data)0; // Return 0 or handle error as needed
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value) {
    if (index < arr->size) {
        arr->data[index] = value;
    }
}

// returns array size
size_t array_size(const Array* arr) {
    if (arr == NULL) {
        return 1;
    }
    return arr->size;
}