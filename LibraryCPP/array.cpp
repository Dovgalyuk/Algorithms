#include "array.h"

struct Array
{
    Data* data;
    size_t size;
};

Array *array_create(size_t size)
{
    Array* array = new Array;
    array->data = new Data[size];
    array->size = size;

    return array;
}

void array_delete(Array *arr)
{
    delete[] arr->data;
    delete arr;
}

Data array_get(const Array *arr, size_t index)
{
    if (index >= arr->size){
        return (Data)0;
    }

    return arr->data[index];
}

void array_set(Array *arr, size_t index, Data value)
{
    if (index >= arr->size){
        return;
    }

    arr->data[index] = value; 

}

size_t array_size(const Array *arr)
{
    return arr->size;
    
}
