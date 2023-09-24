#include "array.h"
#include <cstddef>

struct Array
{
    Data* data;
    size_t size;

    Array(size_t size)
    {
        this->size = size;
        this->data = new Data[size];
    }
};

// create array
Array *array_create(size_t size)
{
    Array arr(size);
    return &arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    delete arr->data;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
   if (index < array_size(arr))
       return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index < array_size(arr))
        arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
