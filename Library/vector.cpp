#include <stdlib.h>
#include "vector.h"

struct Vector
{
	Data* cont;
	size_t size, curr;
};

Vector* vector_create()
{
	Vector* temp = new Vector;
	temp->curr = 0;
	temp->size = 1;
	temp->cont = new Data[temp->size];
	return temp;
}

void vector_delete(Vector* vector)
{
	delete[] vector->cont;
	delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
	return vector->cont[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
	if (index + 1 > vector->curr)
		vector_resize(vector, index + 1);
	vector->cont[index] = value;
}

size_t vector_size(const Vector* vector)
{
	return vector->curr;
}

void vector_resize(Vector* vector, size_t size)
{
	if (size < 1)
		return;
	if (size <= vector->size)
	{
		vector->curr = size;
		return;
	}
	size_t new_size = size;
	if (size >= vector->size)
	{
		new_size = vector->size;
		while (new_size < size)
		{
			new_size *= 2;
		}
	}
	Data* temp = new Data[new_size];
	if (size > vector->curr)
		for (size_t i = 0; i < vector->curr; i++)
			temp[i] = vector->cont[i];
	else
		for (size_t i = 0; i < size; i++)
			temp[i] = vector->cont[i];
	delete[] vector->cont;
	vector->cont = temp;
	vector->curr = size;
	vector->size = new_size;
}
