#include "array.h"

struct Array
{
    Data* data;
    size_t size;
    explicit Array(const size_t arr_size): data(new Data[arr_size]), size(arr_size)  {}
    ~Array() {
        delete[] data;
    }
};

// create array
Array *array_create(const size_t size)
{
    return new Array(size);
}

// delete array, free memory
void array_delete(Array* arr)
{
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, const size_t index)
{
    if (index >= arr->size) {
        return 0;
    }
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (!arr || index >= arr->size) {
        return;
    }
    arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}