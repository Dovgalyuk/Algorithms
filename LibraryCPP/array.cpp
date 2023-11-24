#include <cstddef> 
#include "array.h"
#include <iostream>

using namespace std;

typedef int Data; 


struct Array
{
	Data* data; 
	size_t size; 
};

Array* array_create(size_t size)
{
	Array* arr = new Array;
	arr->data = new Data[size]; 
	arr->size = size;
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
	return Data();
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


int main()
{
	size_t size = 10; 
	Array* arr = array_create(size); 

	
	for (size_t i = 0; i < size; ++i)
	{
		array_set(arr, i, i * 2);
	}

	
	for (size_t i = 0; i < size; ++i)
	{
		cout << "arr[" << i << "] = " << array_get(arr, i) << endl;
	}

	
	array_delete(arr);

	return 0;
}