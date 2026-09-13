#include "array.h"
#include <iostream>
#include <stdexcept>

struct Array
{
    const size_t size;
    Data* data;
};

// create array
Array* array_create(size_t size)
{
    return new Array{
        size,
        new Data[size]{}
    };
}

// delete array, free memory
void array_delete(Array *arr)
{
    if(arr == nullptr) return;

    delete[] arr->data;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if(arr == nullptr){
        throw std::invalid_argument("array hasn't elements");
    }
    if(index >= arr->size){
        throw std::out_of_range("invalid index");
    }

    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if(arr == nullptr){
        throw std::invalid_argument("array hasn't elements");
    }
    if(index >= arr->size){
        throw std::out_of_range("invalid index");
    }

    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    if(arr == nullptr){
        throw std::invalid_argument("array hasn't elements");
    }

    return arr->size;
}
