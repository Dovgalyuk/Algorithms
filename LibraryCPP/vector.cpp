#include "vector.h"

struct Vector
{
    Data* arr;
    int size;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->size = 32;
    vector->arr = new Data[vector->size];
    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->arr;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size)
    {
        return (Data)0;
    }
    return vector->arr[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index < vector->size)
    {
        vector->arr[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    Data* new_arr = new Data[size];
    for (int i = 0; i < size && i < vector->size; i++)
    {
        new_arr[i] = vector->arr[i];
    }
    vector->arr = new_arr;
    vector->size = size;
}
