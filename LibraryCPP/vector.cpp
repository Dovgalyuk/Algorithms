#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;

    Vector() 
    {
       size = 0;
       capacity = 5;
       data = new Data[capacity];
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
    if (vector->capacity > size)
    {
        vector->size = size;
    }
    else {
        size_t temp_capacity = size * 2;
        Data* temp_data = new Data[temp_capacity]{ Data() };

        for (int i = 0; i < vector->size; i++)
        {
            temp_data[i] = vector->data[i];
        }

        delete[] vector->data;

        vector->capacity = temp_capacity;
        vector->size = size;
        vector->data = temp_data;
    }
}
