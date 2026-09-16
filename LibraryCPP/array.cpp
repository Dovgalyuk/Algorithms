#include "array.h"

struct Array
{
    Data* date;
    size_t size;
};

// create array
Array *array_create(size_t size)
{
    Array* arr = new Array();
    arr->date = new Data[size];
    arr->size = size;
    return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
    if (arr == 0) {
        return;
    }
    delete[] arr->date;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if ( arr==0 or arr->date == 0 or index >= arr->size ) {
        return (Data)0;
    }
    return arr->date[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if ( arr==0 or arr->date == 0 or index >= arr->size ) {
        return;
    }
    arr->date[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    if (arr == 0) {
        return 0;
    }
    return arr->size;
}
