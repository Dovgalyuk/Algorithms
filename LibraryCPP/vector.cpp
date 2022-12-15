#include "vector.h"

struct Vector
{
    int size;
    int capasity;
    Data* data;
    Vector()
    {
        size = 0;
        capasity = 10;
        data = new Data[10];
    }
};

Vector* vector_create()
{
    return new Vector();
}

void vector_delete(Vector* vector)
{
    delete vector->data;
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
    if (index >= vector->size)
        return;
    else
        vector->data[index] = value;
}

size_t vector_size(const Vector* vector)
{
    return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (size >= vector->capasity)
    {
        vector->capasity = size * 2; 
        Data* nw = new Data[vector->capasity];
        for (size_t i = 0; i < vector->size; i++)
            nw[i] = vector_get(vector, i);
        for (size_t i = vector->size; i < vector->capasity; i++)
            nw[i] = 0;
        vector->size = size;
        delete[] vector->data;
        vector->data = nw;
    }
    else if (size >= vector->size)
    {
        vector->size = size;
    }
    else
    {
        vector->capasity = size * 2;
        Data* nw = new Data[vector->capasity];
        for (size_t i = 0; i < size; i++)
            nw[i] = vector_get(vector, i);
        for (size_t i = vector->size; i < vector->capasity; i++)
            nw[i] = 0;
        vector->size = size;
        delete[] vector->data;
        vector->data = nw;
    }
}
