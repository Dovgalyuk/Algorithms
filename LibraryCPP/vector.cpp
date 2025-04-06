#include "vector.h"
#include <cstdlib> 

struct Vector
{
    Data*  data;      
    size_t size;      
    size_t capacity;  
};

Vector *vector_create()
{
    Vector* v = new Vector;
    v->size = 0;
    v->capacity = 1; 
    v->data = new Data[v->capacity];
    return v;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size <= vector->size)
    {
        vector->size = size;
        return;
    }
    if (size > vector->capacity)
    {
        size_t newCapacity = vector->capacity;
        while (newCapacity < size)
            newCapacity *= 2;

        Data* newData = new Data[newCapacity];
        for (size_t i = 0; i < vector->size; i++)
            newData[i] = vector->data[i];

        delete[] vector->data;

        vector->data = newData;
        vector->capacity = newCapacity;
    }
    vector->size = size;
}
