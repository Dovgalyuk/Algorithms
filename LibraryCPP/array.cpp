#include "array.h"
#include <stdexcept>

struct Array
{
    size_t size;
    Data* data;

    Array(size_t size) : size(size), data(new Data[size]()) {}
    ~Array() { delete[] data; }
};

// create array
Array *array_create(size_t size)
{
    return new Array(size);
}

// delete array, free memory
void array_delete(Array *arr)
{
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (index >= arr->size) {
        throw std::out_of_range("Index out of range");
    }
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index >= arr->size) {
        throw std::out_of_range("Index out of range");
    }
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
