#include "vector.h"

struct Vector
{
    int* data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->capacity = 4;
    vector->size = 0;
    vector->data = new int[vector->capacity];

    return new Vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size) 
        return 0;

    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index < vector->size)
        vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity) {
        size_t new_cap = vector->capacity * 2;
        while (new_cap < size) 
            new_cap *= 2;

        int* new_data = new int[new_cap];
        for (size_t i = 0; i < vector->size; ++i)
            new_data[i] = vector->data[i];

        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_cap;
    }

    vector->size = size;
}