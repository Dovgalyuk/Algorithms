// array.cpp
#include "array.h"
#include <cstdlib>





Array* array_create(size_t size) {
    Array* arr = new Array;
    arr->data = new Data[size];
    arr->size = size;
    return arr;
}

void array_delete(Array* arr) {
    delete[] arr->data;
    delete arr;
}

Data array_get(const Array* arr, size_t index) {
    if (index < arr->size) {
        return arr->data[index];
    }
    else {
        // handle out of bounds error
        return Data(); // return default value for Data type
    }
}

void array_set(Array* arr, size_t index, Data value) {
    if (index < arr->size) {
        arr->data[index] = value;
    }
    else {
        // handle out of bounds error
    }
}

size_t array_size(const Array* arr) {
    return arr->size;
}
