#include "array.h"

struct Array
{
    Data* values;
    size_t size;
};

// create array
Array *array_create(size_t size)
{
    if (size != 0) {
        Array* arr = new Array;
        arr->size = size;
        arr->values = new Data[size];
        return arr;
    }
    return 0;
}

// delete array, free memory
void array_delete(Array *arr)
{
    delete[] arr->values;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (index < arr->size) {
    return arr->values[index];
    }
    return (Data)0;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index < arr->size) {
    arr->values[index] = value;
    }
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
