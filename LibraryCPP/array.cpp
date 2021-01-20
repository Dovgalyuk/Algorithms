#include <stdlib.h>
#include "array.h"

struct Array
{
	Data* data;
	size_t size;
};

Array* array_create(size_t size)
{
	Array* arr = new Array;
	arr->size = size;
	arr->data = new Data[size];
	return arr;
}

void array_delete(Array* arr)
{
	delete[] arr->data;
	delete arr;
}

Data array_get(const Array* arr, size_t index)
{
	if (index < arr->size)
	{
		return arr->data[index];
	}
	return NULL;
}

void array_set(Array* arr, size_t index, Data value)
{
	if (index < arr->size)
	{
		arr->data[index] = value;
	}
}

size_t array_size(const Array* arr)
{
	return arr->size;
}
