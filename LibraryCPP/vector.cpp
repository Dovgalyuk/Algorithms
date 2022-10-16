#include "vector.h"

struct Vector
{
  Data* data;
  size_t size;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->size = 0;
    vector->data = new Data[0];
    return Vector;
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
    delete vector->data;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index > vector->size)
    {
        vector_resize(vector, index);
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
   return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    size_t new_size = 0;
    Data* data;
    if (size <= vector->size)
    {
        new_size = size;
        data = new Data[new_size];

        for (int i = 0; i < size; i++)
        {
            data[i] = vector->data[i];
        }
    }
    else
    {
        new_size = size > vector->size * 2 ? size : vector->size * 2;
        data = new Data[new_size];

        for (int i = 0; i < vector->size; i++)
        {
            data[i] = vector->data[i];
        }
        for (int i = vector->size - 1; i < new_size; i++)
        {
            data[i] = 0;
        }
    delete[] vector->data;
    vector->data = data;
    vector->size = new_size;
}
