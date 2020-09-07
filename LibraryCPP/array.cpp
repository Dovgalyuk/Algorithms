#include <stdlib.h>
#include "array.h"

struct Array
{
	size_t size;
	Data* array;
};

// create array
Array *array_create(size_t size)
{
	Array* arr = new Array;
	arr->size = size;
	arr->array = new Data[size];
	return arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
	delete[] arr->array;
	delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return arr->array[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
	if(index >= 0 && index <= arr->size)
		arr->array[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
