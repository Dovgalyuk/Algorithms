#include <stdlib.h>
#include "vector.h"

struct Vector
{
	size_t size;
	size_t reserveSize;
	Data* vct;
};

Vector *vector_create()
{
	Vector* vector = new Vector;
	vector->size = 0;
	vector->vct = new Data[0];
	return vector;
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
	delete[] vector->vct;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
	return vector->vct[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
	if (index >= 0 && index <= vector->size)
		vector->vct[index] = value;
}

size_t vector_size(const Vector *vector)
{
	return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
	if (size < vector->reserveSize)
	{
		vector->size = size;
	}
	else
	{
		size_t newSize = size * 2;
		Data* newVector = new Data[newSize];

		for (int i = 0; i < vector->vct[i]; i++)
		{
			newVector[i] = vector->vct[i];
		}
		delete[] vector->vct;
		vector->vct = newVector;
		vector->size = size;
		vector->reserveSize = newSize;
	}
}
