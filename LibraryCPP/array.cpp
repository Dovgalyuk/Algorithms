#include "array.h"

struct Array {
    size_t size;
    Data* data;
};

Array* array_create(size_t size) {
    Array* arr = new Array;
    arr->size = size;
    arr->data = new Data[size];
    return arr;
}

void array_delete(Array* arr) {
    delete[] arr->data;
    delete arr;
}

Data array_get(const Array* arr, size_t index) {
    return arr->data[index];
}

void array_set(Array* arr, size_t index, Data value) {
    arr->data[index] = value;
}

size_t array_size(const Array* arr) {
    return arr->size;
}