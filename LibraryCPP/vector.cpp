#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t sizeMax;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->data = nullptr;
    vector->size = 0;
    vector->sizeMax = 0;
    return vector;
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
    if (index < vector->size)
    {
        return vector->data[index];
    }
    return (Data)0;
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index < vector->size)
    {
        vector->data[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->sizeMax)
    {
        vector->sizeMax = size * 2;
        Data* newData = new Data[vector->sizeMax];
        for (size_t i = 0; i < vector->size; i++)
        {
            newData[i] = vector->data[i];   
        }
        delete[] vector->data;
        vector->data = newData;
    }
    vector->size = size;
}