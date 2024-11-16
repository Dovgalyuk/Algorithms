#include "array.h"
#include <stdexcept>

struct Array
{
    size_t size;
    Data* first;
};

// create array
Array *array_create(size_t size)
{
    if (size == 0) return nullptr;
    Array* arr = (Array*)malloc(sizeof(Array));
    if (!arr) return nullptr;

    arr->size = size;
    arr->first = (Data*)malloc(size * sizeof(Data));
    if (!(arr->first)) {
        free(arr);
        return nullptr;
    }
    return arr;
}
    void array_delete(Array *arr)
{
    if (!arr) return;

    free(arr->first);
    free(arr);
}
Data array_get(const Array *arr, size_t index)
{
    if (!arr)
        throw std::invalid_argument("Array pointer is null");
    if (index >= arr->size)
        throw std::out_of_range("Index out of range");

    return *(arr->first + index);
}
void array_set(Array *arr, size_t index, Data value)
{
    if (!arr)
        throw std::invalid_argument("Array pointer is null");
    if (index >= arr->size)
        throw std::out_of_range("Index out of range");

    *(arr->first + index) = value;
}
size_t array_size(const Array *arr)
{
    if (!arr) throw std::invalid_argument("Array pointer is null");
    return arr->size;
}