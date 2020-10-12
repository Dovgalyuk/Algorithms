#include <stdlib.h>
#include "vector.h"
#include <iostream>

struct Vector
{
    Data* vec;
    size_t size;
    size_t rSize;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->size = 0;
    vector->vec = new Data[0];
    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->vec;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector -> vec[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >=0 && index <= vector -> size)
    {
        vector->vec[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size < vector->rSize)
    {
        vector->size = size;
    }
    else {
        size_t newSize = size*2;
        Data* newVector = new Data[newSize];
        for (int i = 0; i < vector->size; i++)
        {
            newVector[i] = vector->vec[i];
        }
        delete[] vector->vec;
        vector->vec = newVector;
        vector->size = size;
        vector->rSize = newSize;
    }
}
