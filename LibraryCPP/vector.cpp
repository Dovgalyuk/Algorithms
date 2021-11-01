#include <stdlib.h>
#include "vector.h"
#include <iostream>

struct Vector
{
    Data* data;
    size_t size;
    size_t rSzie;
    Vector()
    {
        size = 0;
        rSzie = 0;
        data = NULL;
    }
};

Vector* vector_create()
{
    return new Vector;
}

void vector_delete(Vector* vector)
{
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
    vector->data[index] = value;
}

size_t vector_size(const Vector* vector)
{
    return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (size < vector->rSzie)
        vector->size = size;
    else {
        size_t newSize = size * 2;
        Data* newVector = new Data[newSize];
        for (int i = 0; i < vector->size; i++)
        {
            newVector[i] = vector->data[i];
        }
        delete[] vector->data;
        vector->data = newVector;
        vector->size = size;
        vector->rSzie = newSize;
    }
}