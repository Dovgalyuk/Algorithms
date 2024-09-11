#include "array.h"

struct Array
{
	Data* array;
	size_t size;
};

// create array
Array* array_create(size_t size)
{
	if (size != 0)
	{
		Array* array = new Array;
		array->size = size;
		array->array = new Data[size];
		return array;
	}
	else
		return nullptr;
}

// delete array, free memory
void array_delete(Array* arr)
{
	if (arr != nullptr)
	{
		if (arr->array != nullptr)
		{
			delete[] arr->array;
			delete arr;
		}
	}
}

// returns specified array element
Data array_get(const Array* arr, size_t index)
{
	if (index < arr->size)
		return arr->array[index];
	else
		return 0;
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value)
{
	if (index < arr->size)
	{
		arr->array[index] = value;
	}
}

// returns array size
size_t array_size(const Array* arr)
{
	if (arr != nullptr)
	{
		if (arr->array != nullptr)
			return arr->size;
	}
	return 0;
}

void array_erase(Array* arr, size_t index)
{
	if (index >= 0 && index < arr->size)
	{
		if (index == arr->size - 1)
		{
			arr->array[index] = 0;
		}
		else
		{
			for (size_t i = index; i < array_size(arr) - 1; i++)
			{
				arr->array[i] = arr->array[i + 1];
			}
			arr->array[arr->size - 1] = 0;
		}
	}
}

Array* create_random_array(Data size)
{
	Array* arr = array_create(size);

	for (Data i = 0; i < size; i++)
	{
		Data value = i*15;
		array_set(arr, i, value);
	}
	return arr;
}