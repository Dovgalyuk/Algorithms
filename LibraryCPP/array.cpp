#include "array.h"

struct Array {
    Data* data;
    size_t size;
};

// create array
Array *array_create(size_t size) {
    Array* arr = new Array;
    arr->size = size;

    if (size > 0) {
        arr->data = new Data[size];
        for (size_t i = 0; i < size; i++) {
            arr->data[i] = 0;
        }
    } else {
        arr->data = nullptr;
    }

    return arr;
}

// delete array, free memory
void array_delete(Array *arr) {
    if (arr != nullptr) {
        delete[] arr->data;
        delete arr;
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index) {
    if (arr == nullptr || index >= arr->size) {
        return (Data)0;
    }
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value) {
    if (arr != nullptr && index < arr->size) {
        arr->data[index] = value;
    }
}

// returns array size
size_t array_size(const Array *arr) {
    if (arr != nullptr) {
        return arr->size;
    }
    return 0;
}
