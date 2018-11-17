#include "stdafx.h"
#include <stdlib.h>
#include "array.h"
#include <iostream>

using namespace std;

struct Array
{
	Data* matrix;
	size_t SizeOfMatrix;
};

// create array
Array *array_create(size_t size)
{
	Array* NewMatrix;

	try
	{
		NewMatrix = new Array();
		NewMatrix->matrix = new Data[size];
	}
	catch (bad_alloc xa)
	{
		cout << "The matrix is not created." << endl;
		return NULL;
	}

	for (size_t i = 0; i < size; i++)
	{
		NewMatrix->matrix[i] = 0;
	}

	NewMatrix->SizeOfMatrix = size;
	return NewMatrix;
}

// delete array, free memory
void array_delete(Array *arr)
{
	delete[] arr->matrix;
	delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
	return arr->matrix[index];
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
	arr->matrix[index] = value;
}

// returns array size
size_t array_size(const Array *arr)
{
	return arr->SizeOfMatrix;
}
