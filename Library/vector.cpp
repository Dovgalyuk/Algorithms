#include <stdlib.h>
#include "vector.h"

const int MULTIPLIER = 2;

struct Vector
{
	size_t size = 0;
	size_t rSize = 0;
	Data* element = new Data[0];
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
		vector_resize(vector, index);
	}
	vector->element[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
	if (vector->rSize >= size)
	{
		vector->size = size;
	}
	else if (vector->rSize < size)
	{
		Data* temp = new Data[size * MULTIPLIER];
		for (size_t i = 0; i < vector->size; i++)
		{
			temp[i] = vector->element[i];
		}
		for (size_t i = vector->size; i < size * MULTIPLIER; i++)
		{
			temp[i] = 0;
		}
		delete[] vector->element;
		vector->element = temp;
		vector->size = size;
		vector->rSize = size * MULTIPLIER;
	}
	else
	{
		return;
	}
}