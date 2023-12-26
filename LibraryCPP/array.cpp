#include "array.h"
#include <stdlib.h>

struct Array
{
    size_t ArrSize;
    Data* ArrData;
};

// create array
Array *array_create(size_t size)
{
    Array* NewArray = new Array;
    NewArray->ArrSize = size;
    NewArray->ArrData = new Data[size];
    return new Array;
}

// delete array, free memory
void array_delete(Array *arr)
{
    delete[] arr->ArrData;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return arr->ArrData[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (arr->ArrSize > index && index >= 0)
        arr->ArrData[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->ArrSize;
}
