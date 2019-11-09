#include <stdlib.h>
#include "vector.h"

struct Vector
{
	Data* mVector;
	size_t size, size_really;
};

Vector *vector_create()
{
	Vector *vector = new Vector;
	vector->size = 1;
	vector->size_really = 0;
	vector->mVector = new Data[vector->size];
    return vector;
}

void vector_delete(Vector *vector)
{
	delete[] vector->mVector;
	delete[] vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->mVector[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
	if (index + 1 > vector->size_really) 
	{
		vector_resize(vector, index + 1);
	}
	vector->mVector[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
	if (size <= vector->size) 
	{
		vector->size_really = size;
		return;
	}
	size_t n_size = vector->size;
	while (n_size < size)
	{
		n_size = n_size * 2;
	}
	Data* n_vector = new Data[n_size];
	for (size_t i = 0; i < vector->size_really; i++) 
	{
		n_vector[i] = vector->mVector[i];
	}
	delete[] vector->mVector;
	vector->mVector = n_vector;
	vector->size = n_size;
	vector->size_really = size;
}
