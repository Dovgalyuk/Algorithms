#include"vector.h"

struct Vector
{
	size_t size;
	size_t reserved_size;
	Data* data;
};

Vector *vector_create()
{
	Vector* vector = new Vector;
	vector->size = vector->reserved_size = 0;
	vector->data = new Data[vector->reserved_size];
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

void vector_set(Vector* vector, size_t index, Data value)
{
	if (index + 1 > vector->size)
	{
		if (index + 1 >= vector->reserved_size)
			vector_resize(vector, index + 1);
		else vector->size++;
	}
	vector->data[index] = value;
}

size_t vector_size(const Vector* vector)
{
	return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
	if ((size < vector->size) || (size >= vector->reserved_size)) //could work without that condition in case of function purpose
	{
		vector->reserved_size = size * 2;
		Data* new_data = new Data[vector->reserved_size];

		if (vector->size > 0)
		{
			size_t temp;
			if (vector->size < size)
				temp = vector->size;
			else temp = size;
			for (size_t i = 0; i < temp; i++)
				new_data[i] = vector->data[i];
		}

		delete[] vector->data;
		vector->data = new_data;
		vector->size = size;
	}
}