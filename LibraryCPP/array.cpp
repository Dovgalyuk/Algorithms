#include "array.h"

// create array
Array* array_create(size_t size) {
    return new Array(size);
}

// delete array
void array_delete(Array* arr) {
    delete arr;
}

// get element
Data array_get(const Array* arr, size_t index) {
    return arr->get(index);
}

// set element
void array_set(Array* arr, size_t index, Data value) {
    arr->set(index, value);
}

// size
size_t array_size(const Array* arr) {
    return arr->size();
}
