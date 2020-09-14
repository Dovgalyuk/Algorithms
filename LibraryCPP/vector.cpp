#include <stdlib.h>
#include "vector.h"

struct Vector
{
	size_t size;
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
	Data* tempData = vector->vct;
	Data* newData = new Data[size];

	if (size < vector_size(vector))
	{
		for (int i = 0; i < size; i++)
			newData[i] = vector->vct[i];
	}
	else
	{
		for (int i = 0; i < vector_size(vector); i++)
			newData[i] = vector->vct[i];

		for (int i = vector_size(vector); i < size; i++)
			newData[i] = 0;
	}

	vector->size = size;
	vector->vct = newData;

	delete[] tempData;
}
