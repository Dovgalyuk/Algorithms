#include "array.h"

#include <stdexcept>

struct Array
{
    int* data;
    std::size_t size;
};

Array* array_create(std::size_t size)
{
    Array* array = new Array;

    array->size = size;

    if (size > 0)
        array->data = new int[size]{};
    else
        array->data = nullptr;

    return array;
}

void array_delete(Array** array)
{
    if (array == nullptr || *array == nullptr)
        return;

    delete[] (*array)->data;
    delete *array;

    *array = nullptr;
}

std::size_t array_size(const Array* array)
{
    if (array == nullptr)
        throw std::invalid_argument("Null array");

    return array->size;
}

void array_set(Array* array, std::size_t index, int value)
{
    if (array == nullptr)
        throw std::invalid_argument("Null array");

    if (index >= array->size)
        throw std::out_of_range("Array index out of range");

    array->data[index] = value;
}

int array_get(const Array* array, std::size_t index)
{
    if (array == nullptr)
        throw std::invalid_argument("Null array");

    if (index >= array->size)
        throw std::out_of_range("Array index out of range");

    return array->data[index];
}