#include <stdlib.h>
#include "vector.h"

const size_t INITIAL_SIZE = 64;
const size_t MULTIPLYER = 2;

struct Vector
{
	Data* elements;
	size_t size;
	size_t real_size;
};

Vector* vector_create()
{
	Vector* NewVector = new Vector;
	NewVector->elements = new Data[INITIAL_SIZE];
	NewVector->size = 0;
	NewVector->real_size = INITIAL_SIZE;
	return NewVector;
}

void vector_delete(Vector* vector)
{
	delete[] vector->elements;
	delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{	
	return vector->elements[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
	if (index >= vector->size)
		vector_resize(vector, index + 1);
	vector->elements[index] = value;
}

size_t vector_size(const Vector* vector)
{
	return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
	if (size > vector->real_size) {
		size_t newSize = vector->real_size;
		while (newSize < size) {
			newSize *= MULTIPLYER;
		}
		if (newSize > vector->real_size) {
			Data* newElements = new Data[newSize];
			for (size_t i = 0; i < vector->size; i++) {
				newElements[i] = vector->elements[i];
			}
			delete[] vector->elements;
			vector->elements = newElements;
			vector->real_size = newSize;
		}
		for (size_t i = vector->size; i < size; i++) {
			vector->elements[i] = Data();
		}
	}
	vector->size = size;
}
