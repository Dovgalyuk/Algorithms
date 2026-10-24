#include "array.h"
//#include <climits>

struct Array
{
    Data* date;
    size_t size;
};

// create array
Array *array_create(size_t size)
{
    Array* arr = new Array;
    arr->size = size;
    arr->date = new Data[size];

    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    delete[] arr->date;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (index < arr->size)
    {
        return (arr->date[index]);
    }
    return (Data)0;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index < arr->size)
    {
        arr->date[index] = value;
    }
}

// returns array size
size_t array_size(const Array *arr)
{
    if (arr)
    {
        return arr->size;
    }
    return 0;
}
