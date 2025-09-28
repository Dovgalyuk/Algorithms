#include "array.h"
#include <stdexcept>
using namespace std;

struct Array
{
    Data* data;
    size_t size;
};

// create array
Array *array_create(size_t size)
{
    Array* arr = new Array;
    arr->size = size;
    arr->data = new Data[size]();
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
    if (index >= arr->size) {
        throw out_of_range("Index out of range");
    }
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index >= arr->size) {
        throw out_of_range("Index out of range");
    }
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
