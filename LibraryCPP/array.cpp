#include "array.h"
#include <stdexcept>

struct Array
{
    size_t size_;
    Data* data_;
};

// create array
Array* array_create(size_t size)
{
    Array* arr = new Array;
    arr->size_ = size;
    arr->data_ = new Data[size]();
    return arr;
}

// delete array, free memory
void array_delete(Array* arr)
{
    delete[] arr->data_;
    delete arr;
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    if (index >= arr->size_) {
        throw std::out_of_range("Index out of range");
    }
    return arr->data_[index];
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    if (index >= arr->size_) {
        throw std::out_of_range("Index out of range");
    }
    arr->data_[index] = value;
}

// returns array size
size_t array_size(const Array* arr)
{
    return arr->size_;
}