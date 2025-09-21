#include <stdexcept>
#include "array.h"

struct Array
{
    Data* data;
    size_t size;
};

Array *array_create(size_t size)
{
    Array* arr = new Array;
    arr->size = size;
    arr->data = new Data[size];
    return arr;
}

void array_delete(Array *arr)
{
    if(arr != nullptr){
        delete [] arr->data;
        delete arr;
    }
}

Data array_get(const Array *arr, size_t index)
{
    if(arr == nullptr || index >= arr->size){
        throw std::out_of_range("Index outside the array");
    }
    return arr->data[index];
}

void array_set(Array *arr, size_t index, Data value)
{
    if(arr == nullptr || index >= arr->size){
        throw std::out_of_range("Index outside the array");
    }
    arr->data[index] = value;
}

size_t array_size(const Array *arr)
{
    if(arr == nullptr){
        return 0;
    }
    return arr->size;
}
