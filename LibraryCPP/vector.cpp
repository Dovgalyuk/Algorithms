#include "vector.h"

Vector *vector_create(size_t initial_capacity)
{
    Vector *vector = new Vector;
    vector->data = new Data[initial_capacity];
    vector->capacity = initial_capacity;
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
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t new_size)
{
    if (new_size > vector->capacity)
    {
        size_t new_capacity = (vector->capacity == 0) ? 1 : vector->capacity * 2;
        while (new_size > new_capacity)
        {
            new_capacity *= 2;
        }

        Data *new_data = new Data[new_capacity];
        for (size_t i = 0; i < vector->size; ++i)
        {
            new_data[i] = vector->data[i];
        }

        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }

    vector->size = new_size;
}