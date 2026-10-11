#include "vector.h"

struct Vector
{
    Data *data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector *vector = new Vector;
    vector->size = 0;
    vector->capacity = 0;
    vector->data = nullptr;
    return vector;
}

void vector_delete(Vector *vector)
{
    if (vector != nullptr)
    {
        delete[] vector->data;
        delete vector;
    }
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
    if (new_size <= vector->capacity)
    {
        vector->size = new_size;
        return;
    }

    size_t new_capacity = vector->capacity;

    if (new_capacity == 0) {
        new_capacity = 1;
    }

    while (new_capacity < new_size) {
        new_capacity = new_capacity * 2;
    }

    Data *new_data = new Data[new_capacity];

    for (size_t i = 0; i < vector->size; i++)
    {
        new_data[i] = vector->data[i];
    }

    delete[] vector->data;
    vector->data = new_data;
    vector->capacity = new_capacity;
    vector->size = new_size;
}
