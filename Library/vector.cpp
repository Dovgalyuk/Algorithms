#include <stdlib.h>
#include "vector.h"

struct Vector
{
	Data* a;
	size_t size;
	size_t size_t;
};

Vector* vector_create()
{
	Vector* a = new Vector;
	a->a = new Data[1];
	a->a[0] = 0;
	a->size = 1;
	a->size_t = 1;
	return a;
}

void vector_delete(Vector* vector)
{
	delete[] vector->a;
	delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
	return vector->a[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
	if (index < vector->size_t)
	{
		vector->a[index] = value;
	}
	else if (index < vector->size)
	{
		vector->a[index] = value;
		vector->size_t = index;
	}
	else
	{
		vector_resize(vector, index * 2);
		vector->a[index] = value;
		vector->size_t = index;
	}
}

size_t vector_size(const Vector* vector)
{
	return vector->size_t;
}

void vector_resize(Vector* vector, size_t size)
{
	if (size == 0) {
		vector->size_t = 0;
		vector->a[0] = 0;
	}
	else if (size < vector->size)
	{
		vector->size_t = size;
	}
	else
	{
		Data* a = new Data[size];
		for (int i = 0; i < vector->size; i++)
		{
			a[i] = vector->a[i];
		}
		for (int i = vector->size; i < size; i++)
		{
			a[i] = 0;
		}
		Data* b = vector->a;
		vector->a = a;
		delete[] b;
		vector->size = size;
		vector->size_t = size;
	}

}
