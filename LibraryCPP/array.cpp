#include "array.h"
#include <cassert>

struct Array {
    Data* data;
    size_t size;
};

Array* array_create(size_t size) {
    Array* arr = new Array;
    arr->size = size;
    arr->data = new Data[size];

    for (size_t i = 0; i < size; ++i)
        arr->data[i] = 0;

    return arr;
}

void array_delete(Array* arr) {
    if (!arr)
        return;

    delete[] arr->data;
    delete arr;
}

Data array_get(const Array* arr, size_t index) {
    assert(arr && index < arr->size);
    return arr->data[index];
}

void array_set(Array* arr, size_t index, Data value) {
    assert(arr && index < arr->size);
    arr->data[index] = value;
}

size_t array_size(const Array* arr) {
    assert(arr);
    return arr->size;
}