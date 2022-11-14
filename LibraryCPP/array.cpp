#include "array.h"

struct Array
{
    Data* data;
    size_t size;

    explicit Array(const size_t size): size(size), data(new Data[size]) {}

    ~Array() {
        delete[] data;
    }
};

Array *array_create(size_t size)
{
    return new Array(size);
}

void array_delete(Array *arr)
{
    delete arr;
}

Data array_get(const Array *arr, size_t index)
{
    size_t size = array_size(arr);
    if (index < size) {
        return arr->data[index];
    }
    else {
        return Data();
    }
}

void array_set(Array *arr, size_t index, Data value)
{
    size_t size = array_size(arr);
    if (index < size) {
        arr->data[index] = value;
    }
}

size_t array_size(const Array *arr)
{
    return arr->size;
}

