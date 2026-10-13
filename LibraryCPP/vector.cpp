#include "vector.h"
#include <stdexcept>

struct Vector
{
    Data *data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector *vec = new Vector;
    vec->size = 0;
    vec->capacity = 8;
    vec->data = new Data[vec->capacity];
    return vec;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >= vector->size)
    {
        throw std::out_of_range("Index out of bounds");
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity)
    {
        size_t new_capacity = size * 2;
        Data *new_data = new Data[new_capacity];
        for (size_t i = 0; i < vector->size; i++)
        {
            new_data[i] = vector->data[i];
        }
        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    vector->size = size;
}

void vector_push_back(Vector *vector, Data value)
{
    if (vector->size >= vector->capacity)
    {
        vector_resize(vector, vector->capacity * 2);
    }
    vector->data[vector->size] = value;
    vector->size++;
}

void vector_pop_back(Vector *vector)
{
    if (vector->size > 0)
    {
        vector->size--;
    }
}