
#include "array.h"

#include <stdexcept>


struct Array{
    Data* data;
    std::size_t size;
};


Array* array_create(std::size_t size){
    Array* arr = new Array;

    arr->size = size;
    arr->data = new Data[size];

    return arr;
}

void array_delete(Array* arr){
    if (arr != nullptr)
    {
        delete[] arr->data;
        delete arr;
    }
}

Data array_get(const Array* arr, std::size_t index){
    if (arr == nullptr){
        throw std::invalid_argument("Array is null");
    }

    if (index >= arr->size){
        throw std::out_of_range("Array index out of range");
    }

    return arr->data[index];
}


void array_set(Array* arr, std::size_t index, Data value){
    if (arr == nullptr){
        throw std::invalid_argument("Array is null");
    }

    if (index >= arr->size){
        throw std::out_of_range("Array index out of range");
    }

    arr->data[index] = value;
}


std::size_t array_size(const Array* arr){
    if (arr == nullptr){
        throw std::invalid_argument("Array is null");
    }
    return arr->size;
}
