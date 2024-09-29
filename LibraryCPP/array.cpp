#include "array.h"
#include <iostream>
#include <stdexcept>

struct Array {
    size_t size;
    int* data;
};

// Create array
Array* array_create(size_t size) {
    if (size == 0) {
        throw std::invalid_argument("Size must be greater than 0");
    }

    Array* arr = new Array;
    arr->size = size;
    arr->data = new int[size];  // Выделяем память для целочисленного массива
    return arr;
}

// Delete array, free memory
void array_delete(Array* arr) {
    if (arr) {
        delete[] arr->data;
        delete arr;
    }
}

// Returns specified array element
int array_get(const Array* arr, size_t index) {
    if (index >= arr->size) {
        std::cerr << "Error: Index out of range." << std::endl;
        throw std::out_of_range("Index out of range");
    }
    return arr->data[index];
}

// Sets the specified array element to the value
void array_set(Array* arr, size_t index, int value) {
    if (index >= arr->size) {
        throw std::out_of_range("Index out of range");
    }
    arr->data[index] = value;
}

// Returns array size
size_t array_size(const Array* arr) {
    return arr->size;
}

