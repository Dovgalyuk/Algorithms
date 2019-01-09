#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include "vector.h"

using namespace std;

struct Vector
{
	Data *p;
	size_t size;
	size_t real_size;
};

Vector *vector_create()
{
	Vector* NewVector;

	try
	{
		NewVector = new Vector;
		NewVector->p = new Data[1];
	}
	catch (bad_alloc xa)
	{
		cout << "Vector didn't created" << endl;
		return NULL;
	}

	NewVector->size = 1;
	NewVector->real_size = 1;

	return NewVector;
}

void vector_delete(Vector *vector)
{
	delete[] vector->p;
	delete vector;
}

Data vector_get(Vector *vector, size_t index)
{
	return vector->p[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
	if (index > vector->size)vector_resize(vector, index);
	vector->p[index] = value;
}

size_t vector_size(Vector *vector)
{
	return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
	if (vector->real_size >= size)
	{
		vector->size = size;
	}
	else if (vector->real_size < size)
	{
		Data*NewArray;

		try
		{
			NewArray = new Data[size * 2];
		}
		catch (bad_alloc xa)
		{
			cout << "Vector didn't created" << endl;
			return;
		}

		for (size_t i = 0; i < vector->size; i++)
		{
			NewArray[i] = vector->p[i];
		}

		delete[]vector->p;
		vector->p = NewArray;
		vector->size = size;
		vector->real_size = size * 2;
	}
}
