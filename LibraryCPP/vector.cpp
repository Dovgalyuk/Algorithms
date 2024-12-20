#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t size_max;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->size_max = 1;
    vector->size = 0;
    vector->data = new Data[vector->size_max];
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
    if (size > vector->size_max) {
        size_t new_size_max = vector->size_max;

        while (new_size_max < size) new_size_max *= 2;

        Data* new_data = new Data[new_size_max];
        for (size_t i = 0; i < vector->size; i++) new_data[i] = vector->data[i];
        delete[] vector->data;

        vector->data = new_data;
        vector->size_max = new_size_max;
    }
    vector->size = size;
}
