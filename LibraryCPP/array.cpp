#include "array.h"

struct Array
{
    size_t size_arr;
    Data* data;

    Array(size_t size)
    {
        this->size_arr = size;
        this->data = new Data[size];
    }
};

// create array
Array* array_create(size_t size)
{
    return new Array(size);
}

// delete array, free memory
void array_delete(Array* arr)
{
    delete arr;
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array* arr)
{
    return arr->size_arr;
}
