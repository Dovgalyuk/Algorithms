#include "array.h"
#include <stdexcept> 

struct Array {
    size_t size;  
    Data* data;   

   
    Array(size_t size) {
        this->size = size;
        this->data = new Data[size]; 
    }

    
    ~Array() {
        delete[] data;
    }
};


Array* array_create(size_t size) {
    return new Array(size);
}


void array_delete(Array* arr) {
    delete arr;
}


Data array_get(const Array* arr, size_t index) {
    if (index >= arr->size) {
        throw std::out_of_range("Index out of range in array_get()");
    }
    return arr->data[index];
}


void array_set(Array* arr, size_t index, Data value) {
    if (index >= arr->size) {
        throw std::out_of_range("Index out of range in array_set()");
    }
    arr->data[index] = value;
}

size_t array_size(const Array* arr) {
    return arr->size;
}