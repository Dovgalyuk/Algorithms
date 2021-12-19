#include "vector.h"

struct Vector
{
    Data* arr;
    int size;
    int capacity;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->capacity = 2;
    vector->size = vector->capacity;
    vector->arr = new Data[vector->capacity];
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
    if (size > vector->capacity)
    {
        vector->capacity = size * 2;
        Data* new_arr = new Data[vector->capacity];
        for (int i = 0; i < vector->size; i++)
        {
            new_arr[i] = vector->arr[i];
        }
        delete[] vector->arr;
        vector->arr = new_arr;
    }
     vector->size = size;  
}
