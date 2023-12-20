// array.cpp
#include "array.h"
#include <cstdlib>

Array array_create(size_t size) {
    Array arr;
    arr.size = size;
    arr.data = new int[size];
    return arr;
}

void array_delete(Array& arr) {
    delete[] arr.data;
    // Не требуется delete arr, так как arr является объектом, а не указателем
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

void array_set(Array& arr, size_t index, int value) {
    if (index < arr.size) {
        arr.data[index] = value;
    }
}

size_t array_size(const Array* arr) {
    return arr->size;
}
