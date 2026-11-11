#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector *vector = new Vector;

    vector->data = nullptr;
    vector->size = 0;
    vector->capacity = 0;

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
        size_t capacity = vector->capacity * 2;

        if (capacity < size)
            capacity = size;

        Data* data = new Data[capacity];

        for (size_t i = 0; i < vector->size; ++i)
            data[i] = vector->data[i];

        delete[] vector->data;

        vector->data = data;
        vector->capacity = capacity;
    }

    for (size_t i = vector->size; i < size; ++i)
        vector->data[i] = 0;

    vector->size = size;
}
