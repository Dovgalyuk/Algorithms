#include <stdlib.h>
#include "vector.h"

struct Vector
{
    Data* elem;
    size_t size;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->size = 0;
    vector->elem = new Data[0];
    return vector;
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
    delete vector->elem;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->elem[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index > vector->size) vector_resize(vector, index);
    vector->elem[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    size_t new_size = 0;
    Data* elem;
	if (size <= vector->size)
	{
        new_size = size;
        elem = new Data[new_size];

		for (int i = 0; i < size; i++)
        {
            elem[i] = vector->elem[i];
        }
	}
    else
    {
        new_size = size > vector->size * 2 ? size : vector->size * 2;
        elem = new Data[new_size];

    	for (int i = 0; i < vector->size; i++)
    	{
            elem[i] = vector->elem[i];
    	}
    	for (int i = vector->size - 1; i < new_size; i++)
    	{
            elem[i] = 0;
    	}
    }

    delete[] vector->elem;
    vector->elem = elem;
    vector->size = new_size;
}
