#include <cstdlib>
#include <stdlib.h>
#include "vector.h"

struct Vector
{
	Data* data;
	size_t size;
	size_t reservedSize;
};

Vector *vector_create()
{
	Vector* vector = new Vector;
	vector->data = new Data[0];
	vector->reservedSize = 0;
	vector->size = 0;
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

void vector_set(Vector *vector, size_t index, Data value)
{
	if (index < vector->size)
		vector->data[index] = value;
	else
	{
		if (index < vector->reservedSize)
		{
			vector->size = vector->reservedSize;
			vector->data[index] = value;
		}
		else
		{
			vector->size = index;
			vector_resize(vector, index + vector->reservedSize);
			vector->data[index] = value;
		}
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
		std::free(vector->data);
		vector->data = NULL;
	}
	else
	{
		if (size >= vector->reservedSize)
		{
			if ((vector->data = (Data*)std::realloc(vector->data, size * sizeof(Data) * 2)) == NULL)
				exit(-1);
		}
		else
		{
			vector->size = size;
			return;
		}
	}
	
	vector->size = size;
	vector->reservedSize = vector->size * 2;
}
