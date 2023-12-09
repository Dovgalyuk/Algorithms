#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t max;
};

Vector *vector_create()
{
    Vector* tmp = new Vector;
    tmp->size = tmp->max = 0;
    tmp->data = new Data[0];
    return tmp;
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
    delete[] vector->data;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size)
        return 0;
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >= vector->size)
        return;
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size < vector->max)
    {
        vector->size = size;
        return;
    }
    Data* tmp = new Data[size * 2];
    for (size_t i = 0; i < vector->size; i++)
    {
        tmp[i] = vector->data[i];
    }
    delete[] vector->data;
    vector->size = size;
    vector->max = size * 2;
    vector->data = tmp;
}
