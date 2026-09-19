#include "array.h"

struct Array
{
    Data* data;
    size_t size;
};

// create array
Array* array_create(size_t size)
{
    Array* arr = new Array;
    arr->size = size;
    try
    {
        arr->data = (size > 0) ? new Data[size] : nullptr;
    }
    catch (...)
    {
        delete arr;
        throw;
    }
    return arr;
}

// delete array, free memory
void array_delete(Array* arr)
{
    if (arr != nullptr)
    {
        if (arr->data) delete[] arr->data;
        delete arr;
    }

}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
    if (arr != nullptr && index < arr->size) return arr->data[index];
    return Data{};
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
    if (arr != nullptr && index < arr->size) arr->data[index] = value;
}

// returns array size
size_t array_size(const Array* arr)
{
    if (arr != nullptr) return arr->size;
    return 0;
}
