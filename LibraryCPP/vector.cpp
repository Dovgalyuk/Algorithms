#include "vector.h"
#include <stdexcept>

struct Vector
{
    Data* data;

    size_t cap;
    size_t size;
};

Vector *vector_create()
{
    Vector* vector = new Vector;

    vector->cap = 10;
    vector->size = 0;

	vector->data = new Data[vector->cap];

    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index < vector->size) return vector->data[index];
    else return { -1, -1 };
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (vector->size <= index) throw std::invalid_argument("Out of range");

    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->cap) {
        while (vector->cap < size) vector->cap *= 2;

        Data* new_arr = new Data[vector->cap];

        for (size_t i = 0; i < vector->size; i++) {
            new_arr[i] = vector->data[i];
        }

        delete[] vector->data;
        vector->data = new_arr;
    }
    vector->size = size;
}
