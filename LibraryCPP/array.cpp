#include <stdlib.h>
#include "array.h"

struct Array
{
	size_t size;
	Data *pArr;
};

// create array
Array *array_create(size_t size)
{
	Array* new_arr =new Array;
	new_arr->size =size;
	new_arr->pArr =new Data[size];
    return new_arr;
}

// delete array, free memory
void array_delete(Array *arr)
{
	delete[] arr->pArr;
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
	if(0 <= index && index < arr->size)
		return (arr->pArr)[index];
	return (Data)0;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
	if(0 <= index && index < arr->size)
		 (arr->pArr)[index] =value;
}

// returns array size
size_t array_size(const Array *arr)
{
    return arr->size;
}
