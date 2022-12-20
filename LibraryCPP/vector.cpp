#include "vector.h"
#include <iostream>
using namespace std;

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;
    Vector()
    {
        capacity = 1;
        size = 0;
        data = new Data[capacity];
    }
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index < vector->size)
    {
        return vector->data[index];
    }
    else
    {
        cout << "Error: out of range" << '\n';
        return false;
    }
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index < vector->size)
    {
        vector->data[index] = value;
    }
    else
    {
        cout << "Error: out of range" << '\n';
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size <= vector->capacity)
    {
        vector->size = size;
    }
    else
    {
        size_t newCapacity = size * 2;
        Data* tmpData = new Data[newCapacity];
        for (int i = 0; i < vector->size; i++)
        {
            tmpData[i] = vector->data[i];
        }
        delete[] vector->data;
        vector->capacity = newCapacity;
        vector->size = size;
        vector->data = tmpData;
    }
}
