#include <stdlib.h>
#include "vector.h"

struct Vector
{
	Data* arr;
	size_t size, real_size;
};

Vector* vector_create()
{
	Vector* vec = new Vector;
	vec->arr = new Data[1];
	vec->arr[0] = 0;
	vec->size = 1;
	vec->real_size = 1;
	return vec;
}

void vector_delete(Vector* vector)
{
	delete[] vector->arr;
	delete[] vector;
}

Data vector_get(const Vector* vector, size_t index)
{
	return vector->arr[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
	if (index < vector->real_size)
	{
		vector->arr[index] = value;
	}
	else if (index < vector->size)
	{
		vector->real_size = index;
		vector->arr[index] = value;
	}
	else
	{
		vector_resize(vector, index * 2);
		vector->real_size = index;
		vector->arr[index] = value;
	}
}

size_t vector_size(const Vector* vector)
{
	return vector->real_size;
}

void vector_resize(Vector* vector, size_t size)
{
	if (size == 0) {
		vector->real_size = 0;
		vector->arr[0] = 0;
	}
	else if (size < vector->size)
	{
		vector->real_size = size;
	}
	else
	{
		Data* arr2 = new Data[size];
		for (int i = 0; i < vector->size; i++)
		{
			arr2[i] = vector->arr[i];
		}
		for (int i = vector->size; i < size; i++)
		{
			arr2[i] = 0;
		}
		Data* del = vector->arr;
		vector->arr = arr2;
		delete[] del;
		vector->size = size;
		vector->real_size = size;
	}

}