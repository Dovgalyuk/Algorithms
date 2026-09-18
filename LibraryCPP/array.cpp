#include "array.h"

struct Array
{
    size_t size;
    Data* data;
};

// create array
Array *array_create(size_t size)
{
    Array *arr = new Array();
    arr->size = size;
    arr->data = (size > 0) ? new Data[size] : nullptr;
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr == nullptr) {
        return;
    }
    delete[] arr->data;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (arr == nullptr || index >= arr->size) {
        return (Data)0;
    }
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (arr == nullptr || index >= arr->size) {
        return;
    }
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    if (arr == nullptr) {
        return 0;
    }
    return arr->size;
}
