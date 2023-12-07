#include "vector.h"

struct Vector
{
    size_t size;
    Data* data;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->data = NULL;
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
    if (index < vector->size) {
		return vector->data[index];
    }
    return 0;
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index < vector->size) {
		vector->data[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size == vector->size) {
        return;
    }
    Data* newData = new Data[size];
    size_t minSize = size < vector->size ? size : vector->size;
    for (size_t i = 0; i < minSize; i++) {
        newData[i] = vector->data[i];
    }
    delete[] vector->data;
    vector->data = newData;
    vector->size = size;
}
