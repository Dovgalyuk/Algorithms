#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t max_size;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->max_size = 1;
    vector->size = 0;
    vector->data = new Data[vector->max_size];
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
    return 0;
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index < vector->size) vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->max_size) {
        size_t new_max_size = vector->max_size;

        while (new_max_size < size) new_max_size *= 2;

        Data* new_data = new Data[new_max_size];
        for (size_t i = 0; i < vector->size; i++) new_data[i] = vector->data[i];
        delete[]vector->data;

        vector->data = new_data;
        vector->max_size = new_max_size;
    }
    vector->size = size;
}
