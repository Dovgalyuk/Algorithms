#include "array.h"

struct Array
{
    size_t size;
    int *data;
};

// create array
Array *array_create(size_t size)
{
    Array* newArr = new Array;
    newArr->data = new int[size]{0};
    newArr->size = size;
    return newArr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    delete[] arr->data;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if(index < arr->size){
        arr->data[index] = value;
    }
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
