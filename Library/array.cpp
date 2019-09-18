#include <stdlib.h>
#include "array.h"

struct Array
{
	size_t length;
	Data* elements;
};

// create array
Array *array_create(size_t size)
{
	Array* newArr = new Array();
	newArr->length = size;
	newArr->elements = new Data[size];
    return (newArr);
}

// delete array, free memory
void array_delete(Array *arr)
{
	delete[] arr->elements;
	delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return arr->elements[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
	arr->elements[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->length;
}
