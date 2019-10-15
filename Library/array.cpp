#include <stdlib.h>
#include "array.h"

struct Array
{
	Data* mArray;
	size_t size;
};

Array* array_create(size_t size)
{
	Array* arr = new Array;
	arr->size = size;
	arr->mArray = new Data[arr->size];
	return arr;
}

void array_delete(Array* arr)
{
	delete[] arr->mArray;
	delete arr;
}

Data array_get(const Array* arr, size_t index)
{
	return arr->mArray[index];
}

void array_set(Array* arr, size_t index, Data value)
{
	if (index >= 0 && index < arr->size)
	{
		arr->mArray[index] = value;
	}
}

size_t array_size(const Array* arr)
{
	return arr->size;
}
