#include "vector.h"

struct Vector
{
    Data *elements;
    size_t current_size;
    size_t array_capacity;
};

Vector *vector_create()
{
    Vector *vector = new Vector;
    vector->elements = nullptr;
    vector->current_size = 0;
    vector->array_capacity = 0;
    return vector;
}

void vector_delete(Vector *vector)
{
    if (vector == nullptr)
    {
        return;
    }

    delete[] vector->elements;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->current_size)
    {
        return 0;
    }

    return vector->elements[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index < vector->current_size)
    {
        vector->elements[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->current_size;
}

void vector_resize(Vector *vector, size_t new_size)
{
    if (new_size > vector->array_capacity)
    {
        size_t new_capacity = vector->array_capacity;

        if (new_capacity == 0)
        {
            new_capacity = 4;
        }

        while (new_capacity < new_size)
        {
            new_capacity = new_capacity * 2;
        }

        Data *new_elements = new Data[new_capacity];

        for (size_t i = 0; i < vector->current_size; i = i + 1)
        {
            new_elements[i] = vector->elements[i];
        }

        delete[] vector->elements;
        vector->elements = new_elements;
        vector->array_capacity = new_capacity;
    }

    for (size_t i = vector->current_size; i < new_size; i = i + 1)
    {
        vector->elements[i] = 0;
    }

    vector->current_size = new_size;
}
