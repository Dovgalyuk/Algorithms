#include <stdlib.h>
#include "array.h"

struct Array
{
	int *data;
	int size;
};

// create array
Array *array_create(size_t size)
{
	Array* arr = new Array;
	arr->size = size;
	arr->data = new int[size];
	return arr;
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
	if (0 <= index && index < arr->size)
		return (arr->data)[index];
	return (Data)0;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
	if (0 <= index && index < arr->size)
		(arr->data)[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
