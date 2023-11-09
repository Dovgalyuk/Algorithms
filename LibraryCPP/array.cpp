#include "array.h"

struct Array
{
    const size_t size;
    Data *values;
};

Array *array_create(size_t size)
{
    Array *arr = new Array{size, new Data[size]};
    return arr;
}

void array_delete(Array *arr)
{
    delete arr;
}

Data array_get(const Array *arr, size_t index)
{
    if (index < arr->size) {
        return arr->values[index];
    } else {
        return 0;
    }
}

void array_set(Array *arr, size_t index, Data value)
{
    if (index < arr->size) {
        arr->values[index] = value;
    }
}

size_t array_size(const Array *arr)
{
    return arr->size;
}