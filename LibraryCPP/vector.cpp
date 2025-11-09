#include "vector.h"

struct Vector
{
	Data* data;
	size_t size;
	size_t capacity;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    v->size = 0;
	v->capacity = 4;
	v->data = new Data[v->capacity];
    return vector
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
	if (index < v->size) {
		v->data[index] = value;
	}
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
	if (size > v->capacity) {
		while (v->capacity < size) {
			v->capacity *= 2;
		}
		Data* new_data = new Data[v->capacity];
		for (size_t i = 0; i < v->size; i++) {
			new_data[i] = v->data[i];
		}
		delete[] v->data;
		v->data = new_data;
	}
	v->size = size;
}
