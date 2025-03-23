#include "array.h"
#include <iostream>
#include <stdexcept>

struct Array
{
    Data* data;
    size_t size;
};

// create array
Array *array_create(size_t size)
{
    Array* arr = new Array;
    if (!arr) {
        return nullptr;
    }

    arr->data = new Data[size];
    if(!arr->data) {
        delete arr;
        return nullptr;
    }

    arr->size = size;

    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr) {
        delete[] arr->data;
        delete arr;
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    /*if (!arr) {
        throw std::invalid_argument("Array is null");
    }
    if(index >= arr->size){
        throw std::out_of_range("Index out of range");
    }*/
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if(!arr){
        throw std::invalid_argument("Array is null");
    }
    if(index >= arr->size){
        throw std::out_of_range("Index out of range");
    }
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    if (!arr) {
        return 0;
    }
    return arr->size;
}
