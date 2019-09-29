#include <stdlib.h>
#include "vector.h"

struct Vector
{
	size_t size = 0;
	int* element = new int[0];
};

Vector *vector_create()
{
	Vector* vector = new Vector;
	return vector;
}

void vector_delete(Vector *vector)
{
	delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
	if (!vector)
	{		
		throw("Vector is empty. Unable to get element!");
		return 0;
	}
	else if (vector->size < index)
	{
		throw("Unable to find this element!");
		return 0;
	}
	else
	{
		return vector->element[index];
	}
}

void vector_set(Vector *vector, size_t index, Data value)
{
	if (!vector)
	{
		throw("Vector is empty. Unable to get elements!");
		return;
	}
	else if (index > vector->size)
	{
		int* temp = new int[index];
		for (size_t i = 0; i < vector->size; i++)
		{
			temp[i] = vector->element[i];
		}
		for (size_t i = vector->size; i < index; i++)
		{
			temp[i] = 0;
		}
		delete[] vector->element;
		temp[index - 1] = value;
		vector->element = temp;
		vector->size = index;
	}
	else
	{
		vector->element[index] = value;
	}
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
	int* temp = new int[size];
	if (vector->size > size)
	{
		for (size_t i = 0; i < size; i++)
		{
			temp[i] = vector->element[i];
		}
		delete[] vector->element;
		vector->element = temp;
		vector->size = size;
	}
	else if (vector->size < size)
	{
		for (size_t i = 0; i < vector->size; i++)
		{
			temp[i] = vector->element[i];
		}
		for (size_t i = vector->size; i < size; i++)
		{
			temp[i] = 0;
		}
		delete[] vector->element;
		vector->element = temp;
		vector->size = size;
	}
	else
	{
		return;
	}
}
