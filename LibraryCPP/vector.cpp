#include <stdlib.h>
#include "vector.h"

struct Vector
{
	Data* point;
	size_t size;
};

Vector *vector_create()
{
    Vector* new_vector = new Vector;
    new_vector->point = nullptr;
    new_vector->size = 0;
    return new_vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->point;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index < vector->size && index >= 0)
        return vector->point[index];
    return (Data)0;
}

void vector_set(Vector *vector, size_t index, Data value)
{
	if (index <= vector->size)
	{
		if (index == vector->size)
		{
			if (vector->size == 0)
			{
				vector->point = new Data;
				vector->point[0] = value;
				vector->size = 1;
			}
			else
			{
				Data* new_point = new Data[2 * (vector->size)];

				for (size_t i = 0; i < vector->size; i++)
					new_point[i] = vector->point[i];
				for (size_t i = vector->size + 1; i < 2 * (vector->size); i++)
					new_point[i] = (Data)0;

				vector->size *= 2;
				delete[] vector->point;
				vector->point = new_point;
			}
		}
		vector->point[index] = value;
	}
}

size_t vector_size(const Vector *vector)
{
	return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
	if (size == 0)
	{
		delete[] vector->point;
		vector->point = nullptr;
	}
	else
	{
		Data* new_point = new Data[size];
		int i;
		for (i = 0; i < size && i < vector->size; i++)
			new_point[i] = vector->point[i];
		for (; i < size; i++)
			new_point[i] = (Data)0;
		delete[] vector->point;
		vector->point = new_point;
	}
	vector->size = size;
}
