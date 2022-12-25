#include "vector.h"

struct Vector
{
    int size;
    int capasity;
    Data* data;
};

Vector* vector_create()
{
    Vector* vector = new Vector;
    vector->size = vector->capasity= 0;
    vector->data = new Data[vector->capasity];
    return vector;
}

void vector_delete(Vector* vector)
{
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    if (index >= vector->size)
        return 0;
    else
        return (vector->data[index]);
}

void vector_set(Vector* vector, size_t index, Data value)
{
    if (index < vector->size)
    {
        vector->data[index] = value;
    }
    else
    {
        vector_resize(vector, index + 1);
        vector->data[index] = value;
    }
}

size_t vector_size(const Vector* vector)
{
 
    return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (size <= vector->capasity)
    {
        vector->size = size;
    }
    else
    {
        size_t newSize = size * 2;
        Data* newData = new Data[newSize];

        for (size_t i = 0; i < vector->size; i++)
        {
            newData[i] = vector->data[i];
        }

        delete[] vector->data;
        vector->data = newData;
        vector->size = size;
        vector->capasity = newSize;
    }
}
