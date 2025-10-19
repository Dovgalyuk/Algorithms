#include "vector.h"

Vector *vector_create()
{
    size_t initial_capacity = 4;
    Vector *vec = new Vector;

    vec -> capacity = initial_capacity;
    vec -> size = 0;
    vec -> data = new Data[initial_capacity];

    return vec;
}

void vector_delete(Vector *vec)
{
    // TODO: free vector internals
    if (vec != nullptr)
    {
        delete[] vec -> data;
        delete vec;
    } 
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >= vector -> capacity)
        vector_resize(vector, index);
    
    vector -> data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}
size_t vector_capacity(const Vector *vector)
{
    return vector->capacity;
}

void vector_resize(Vector *vector, size_t req_size)
{
    if (vector == nullptr) return;

    if (req_size > vector->capacity)
    {
        size_t new_capacity = vector -> capacity;
        while (new_capacity < req_size)
            new_capacity *= 2;

        Data *new_data = new Data[new_capacity];

        for (size_t i = 0; i < vector -> size; i++)
            new_data[i] = vector->data[i];

        for (size_t i = vector->size; i < req_size; i++)
            new_data[i] = 0;

        delete[] vector->data;
        vector -> data = new_data;
        vector -> capacity = new_capacity;
        vector -> size = req_size;
    }

    else if (req_size > vector->size)
    {
        for (size_t i = vector -> size; i < req_size; i++)
            vector -> data[i] = 0;

        vector -> size = req_size;
    }

    else
    {
        vector -> size = req_size;
    }
}

