#include "array.h"

struct Array {
    Data* elem;
    size_t size;
};

// create array
Array* array_create(size_t size) {
    Array* arr = new Array;
    arr->size = size;
    arr->elem = new Data[size];
    return arr;
}

// delete array, free memory
void array_delete(Array* arr) {
    delete[] arr->elem;
    delete arr;
}

// returns specified array element
Data array_get(const Array* arr, size_t index) {
    return arr->elem[index];
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value) {
    arr->elem[index] = value;
}

// returns array size
size_t array_size(const Array* arr) {
    return arr->size;
}