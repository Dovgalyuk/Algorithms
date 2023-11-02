#include "array.h"

struct Array
{
    Data* data;
    size_t size;

    Array(size_t size) {
        this->size = size;
        this->data = new Data[size];
    }

    ~Array() {
        delete[] data;
    }
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
    size_t size = array_size(arr);
    if (index < size) return arr->data[index];
    return (Data)0;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    size_t size = array_size(arr);
    if (index < size) arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
