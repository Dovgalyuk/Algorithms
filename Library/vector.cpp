#include <stdlib.h>
#include "vector.h"

struct Vector
{
	Data* mass;
	size_t size;
	size_t size_t;
};

Vector* vector_create()
{
	Vector* a = new Vector;
	a->mass = new Data[1];
	a->size = 1;
	a->mass[0] = 0;
	a->size_t = 0;
	return a;
}

void vector_delete(Vector* vector)
{
	delete vector->mass;
	delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
	return vector->mass[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
	if (index < vector->size) {
		(vector->mass)[index] = value;
		if (index > vector->size_t)
			vector->size_t = index;
	}
	else {
		while (index >= vector->size) {
			vector_resize(vector, (vector->size) * 2);
		}
		vector->mass[index] = value;
		if (index > vector->size_t)
			vector->size_t = index;
	}
}

size_t vector_size(const Vector* vector)
{
	return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
	size_t min;
	if (size < vector->size)
	{
		min = size;
		vector->size = size;
	}
	else min = vector->size;
	Data* b;
	if (size == 0) {
		b = new Data[1];
	}
	else
		b = new Data[size];
	for (int i = 0; i < size; i++)
		b[i] = 0;
	if (size == 0) {
		b[0] = 0;
	}
	if (min == 0) {
		b[0] = vector->mass[0];
		vector->size = 1;
	}
	else
		for (int i = 0; i < min; i++)
			b[i] = vector->mass[i];
	vector->size = size;
	Data* del = vector->mass;
	vector->mass = b;
	delete del;
}