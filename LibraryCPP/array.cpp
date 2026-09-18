#include "array.h"

struct Array
{
    size_t size;
    Data* data;
};

// create array
Array *array_create(size_t size)
{
    Array* arr = new Array();
    arr->size = size;
    arr->data = (size > 0) ? new Data[size] : nullptr;
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr != nullptr) {
        delete[] arr->data;
        delete arr;
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (arr == nullptr or index >= arr->size) {
        return Data(0);
    }
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (arr and index < arr->size) {
        arr->data[index] = value;
    }
}

// returns array size
size_t array_size(const Array *arr)
{
    return (arr != nullptr) ? arr->size : 0;
}
