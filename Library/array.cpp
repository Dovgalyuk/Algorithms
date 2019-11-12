#include <stdlib.h>
#include "array.h"

struct Array
{
	Data* cont;
	size_t size;
};


Array *array_create(size_t size)
{
	Array* temp = new Array;
	temp->cont = new Data[size];
	temp->size = size;
	return temp;
}


void array_delete(Array *arr)
{
	delete[] arr->cont;
	delete arr;
}


Data array_get(const Array *arr, size_t index)
{
    return arr->cont[index];
}


void array_set(Array *arr, size_t index, Data value)
{
	arr->cont[index] = value;
}


size_t array_size(const Array *arr)
{
    return arr->size;
}
