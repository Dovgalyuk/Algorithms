#include <stdlib.h>
#include "vector.h"

struct Vector
{
	Data* cont;
	size_t size, real_size;
};

Vector *vector_create()
{
	Vector* temp = new Vector;
	temp->size = 0;
	temp->real_size = 2;
	temp->cont = new Data[temp->real_size];
    return temp;
}

void vector_delete(Vector *vector)
{
	delete[] vector->cont;
	delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->cont[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
	if (index + 1 > vector->size)
		vector_resize(vector, index + 1);
	vector->cont[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
	if (size <= vector->real_size)
	{
		vector->size = size;
		return;
	}
	if (size < 1)
		return;
	size_t new_size;
	if (size < vector->real_size)
		new_size = size;
	else
	{
		new_size = vector->real_size;
		while (new_size < size)
		{
			new_size *= 2;
		}
	}
	Data* temp = new Data[new_size];
	if (size > vector->real_size)
		for (size_t i = 0; i < vector->size; i++)
			temp[i] = vector->cont[i];
	else
		for (size_t i = 0; i < size; i++)
			temp[i] = vector->cont[i];
	delete[] vector->cont;
	vector->cont = temp;
	vector->size = size;
	vector->real_size = new_size;
}
