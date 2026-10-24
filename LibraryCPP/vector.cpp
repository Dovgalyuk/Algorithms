#include "vector.h"

struct Vector
{
    Data *data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    if (!vector) return;
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

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity)
    {
        size_t new_cap = vector->capacity ? vector->capacity : 4;
        while (new_cap < size) new_cap *= 2;

        Data *new_data = new Data[new_cap];
        for (size_t i = 0; i < vector->size; ++i)
            new_data[i] = vector->data[i];

        delete[] vector->data;
        vector->data     = new_data;
        vector->capacity = new_cap;
    }
    vector->size = size;
}