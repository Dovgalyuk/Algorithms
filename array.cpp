#include "array.h"
#include <stdexcept>

Array* array_create(size_t size)
{
    Array* arr = new Array;
    arr->size = size;
    arr->data = size > 0 ? new Data[size] : nullptr;

    for (size_t i = 0; i < size; i++)
    {
        arr->data[i] = 0;
    }

    return arr;
}

void array_destroy(Array* arr)
{
    if (arr == nullptr)
    {
        return;
    }

    delete[] arr->data;
    delete arr;
}

size_t array_size(const Array* arr)
{
    return arr->size;
}

Data array_get(const Array* arr, size_t index)
{
    if (index >= arr->size)
    {
        throw std::out_of_range("array_get: индекс выходит за границы массива");
    }

    return arr->data[index];
}

void array_set(Array* arr, size_t index, Data value)
{
    if (index >= arr->size)
    {
        throw std::out_of_range("array_set: индекс выходит за границы массива");
    }

    arr->data[index] = value;
}
