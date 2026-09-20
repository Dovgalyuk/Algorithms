#include "array.h"
#include <stdlib.h>

struct Array
{
    size_t size;
    Data* data;
    FFree free;
};


// create array
Array* array_create(size_t size, FFree f)
{
    Array* arr = new Array;

    arr->size = size;
    arr->data = new Data[size]{};
    arr->free = f;

    return arr;
}


// delete array, free memory
void array_delete(Array* arr)
{
    if (arr == nullptr)
        return;

    // Если была передана функция освобождения данных
    if (arr->free != nullptr)
    {
        for (size_t i = 0; i < arr->size; i++)
        {
            arr->free((void*)arr->data[i]);
        }
    }

    delete[] arr->data;
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
    return arr->size;
}