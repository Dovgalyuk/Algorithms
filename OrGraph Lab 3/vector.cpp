#include <stdlib.h>
#include <iostream>
#include "vector.h"

struct Vector
{
	Data* vector;
	size_t size;
	size_t capacity;
};

Vector *vector_create()
{
	Vector* newVector = new Vector();
	newVector->vector = new Data[1];
	newVector->size = 1;
	newVector->capacity = 1;
	return newVector;
}

void vector_delete(Vector *vector)
{
	delete[] vector->vector;
	delete vector;
}

Data vector_get(Vector *vector, size_t index)
{
	if (index >= vector->size) return 0;
	return vector->vector[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
	if (index >= vector->size){
		vector_resize(vector, index + 1);
	}

	vector->vector[index] = value;
}

size_t vector_size(Vector *vector)
{
	return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
	if (size <= vector->capacity){
		vector->size = size;
	}
	else	{
		Data* newVector = new Data[2 * size];
		for (size_t i = 0; i < vector->size; i++)
		{
			newVector[i] = vector->vector[i];
		}
		delete[] vector->vector;
		vector->vector = newVector;
		vector->size = size;
		vector->capacity = 2 * size;
	}
}
