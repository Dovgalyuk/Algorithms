#include "array.h"

struct Array
{
    Data* arr;
    size_t size;
};

// create array
Array *array_create(size_t size)
{
    Array* arr = new Array;
    arr->size = size;
    arr->arr = new Data[size]();

    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    delete[] arr->arr;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if(index>=arr->size){
        return (Data)0;
    }

    return arr->arr[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if(index>=arr->size){
        return;
    }

    arr->arr[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}