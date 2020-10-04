#include <cstdlib>
#include <stdlib.h>
#include "vector.h"

struct Vector
{
	Data* data;
	size_t size;
	size_t reservedSize;
};

Vector *vector_create()
{
	Vector* vector = new Vector;
	vector->data = new Data[0];
	vector->reservedSize = 0;
	vector->size = 0;
	return vector;
}

void vector_delete(Vector *vector)
{
	delete[] vector->data;
	delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
	return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
	if (index < vector->size)
		vector->data[index] = value;
	else
	{
		vector_resize(vector, index + 1);
		vector->data[index] = value;
	}
}

size_t vector_size(const Vector *vector)
{
	return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
	if (size < vector->reservedSize)
		vector->size = size;
	else
	{
		size_t newSize = size * 2;
		Data* newData = new Data[newSize];
		
		for (size_t i = 0; i < vector->size; i++)
			newData[i] = vector->data[i];
		
		delete[] vector->data;

		vector->data = newData;
		vector->size = size;
		vector->reservedSize = newSize;
	}
}
