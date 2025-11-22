#include "vector.h"

struct Vector
{
    Data *data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector *v = new Vector;
    v->data = nullptr;
    v->size = 0;
    v->capacity = 0;
    return v;
}

void vector_delete(Vector *vector)
{
    if (vector->data != nullptr)
    {
        delete[] vector->data;
    }
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
        size_t new_capacity = vector->capacity == 0 ? 1 : vector->capacity;
        while (new_capacity < size)
        {
            new_capacity *= 2;
        }
        
        Data *new_data = new Data[new_capacity];
        for (size_t i = 0; i < vector->size; i++)
        {
            new_data[i] = vector->data[i];
        }
        if (vector->data != nullptr)
        {
            delete[] vector->data;
        }
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    vector->size = size;
}
