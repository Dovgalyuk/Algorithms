#include "array.h"

struct Array
{
    Data* array;
    size_t size;
};

// create array
Array *array_create(size_t size)
{
    if(size !=  0) {
        Array* array = new Array;
        array->size = size;
        array->array = new Data[size];

        return array;
    }
    else {
        return nullptr;
    }
}

// delete array, free memory
void array_delete(Array *arr)
{
     if (arr) {
        delete[] arr->array;
        delete arr;
    }
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    if (index < arr->size)
		return arr->array[index];
	else
		return 0;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
    if (index < arr->size)
	{
		arr->array[index] = value;
	}
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr ? arr->size : 0;
}
