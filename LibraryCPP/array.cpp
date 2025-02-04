#include "array.h"

struct Array {
    size_t size; 
    Data* data;  

    Array(size_t size) {
        this->size = size;
        this->data = new Data[size];
    }

    ~Array() {
        delete[] data;
    } // Деструктор
};

Array* array_create(size_t size) {
    return new Array(size);
}

void array_delete(Array* arr) {
    delete arr;
}

Data array_get(const Array* arr, size_t index) {
    if (index >= arr->size) return 0; 
    return arr->data[index];
}

void array_set(Array* arr, size_t index, Data value) {
    if (index < arr->size) {
        arr->data[index] = value;
    }
}

size_t array_size(const Array* arr) {
    return arr->size;
}
