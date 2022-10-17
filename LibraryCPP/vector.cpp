#include "vector.h"

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
    // TODO: free vector internals
    delete[] vector->data;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{

    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
   if (index < vector->size)
   {
	vector->data[index] = value;
   }
   else
   {
	vector_resize(vector, index + 1);
	vector->data[index] = value;
   }
}

void vector_resize(Vector *vector, size_t size)
{
   	if (size < vector->reserved_size)
	{
		vector->size = size;
	}
	else
	{
		size_t newSize = size * 2;
		Data* newData = new Data[newSize];

		for (size_t i = 0; i < vector->size; i++)
			newData[i] = vector->data[i];

		delete[] vector->data;

		vector->data = newData;
		vector->size = size;
		vector->reserved_size = newSize;
	}
}
