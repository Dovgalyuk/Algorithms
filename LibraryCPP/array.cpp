#include "array.h"

struct Array
{
    Data* data;
    size_t size;

    Array(size_t size)
    {
        this->size = size;
        this->data = new Data[size];
        for (size_t i = 0; i < size; ++i)
        {
            this->data[i] = Data();
        }
    }
};

// create array
Array* array_create(size_t size)
{
    Array* arr = new Array(size);
    return arr;
}

// delete array, free memory
void array_delete(Array* arr)
{
    delete[] arr->data;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (index >= arr->size) return 0;
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index < arr->size) arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}