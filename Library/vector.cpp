#include <stdlib.h>
#include "vector.h"

const int MULTIPLIER = 2;

struct Vector
{
	size_t size;
	size_t rSize;
	Data* element;
};

Vector *vector_create()
{
	Vector* vector = new Vector;
	vector->size = 1;
	vector->rSize = 1;
	vector->element = new Data[vector->rSize];
	return vector;
}

void vector_delete(Vector *vector)
{
	delete[] vector->element;
	delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
	if (!vector)
	{
		throw("Vector is not created.");
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
		throw("Vector is not created.");
		return;
	}
	else if (index + 1 > vector->size)
	{
		vector_resize(vector, index + 1);
	}
	vector->element[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
	if (size <= vector->rSize)
	{
		vector->size = size;
		return;
	}
	if (size < 1)
	{
		return;
	}
	size_t newSize;
	if (size < vector->rSize)
	{
		newSize = size;
	}
	else
	{
		newSize = vector->rSize;
		while (newSize < size)
		{
			newSize *= 2;
		}
	}
	Data* temp = new Data[newSize];
	if (size > vector->rSize)
	{
		for (size_t i = 0; i < vector->size; i++)
		{
			temp[i] = vector->element[i];
		}
	}
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			temp[i] = vector->element[i];
		}
	}
	delete[] vector->element;
	vector->element = temp;
	vector->size = size;
	vector->rSize = newSize;
}