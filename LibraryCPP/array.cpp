#include <stdlib.h>
#include "array.h"

struct Array
{
	Data* data;
	size_t arrSize;
};

// create array
Array *array_create(size_t size)
{
	Array* arr = new Array;
	arr->arrSize = size;
	arr->data = new Data[size];
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
	return arr->data[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
	if (index >= 0 && index < arr->arrSize)
		arr->data[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
	return arr->arrSize;
}
