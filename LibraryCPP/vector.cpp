#include "vector.h"

struct Vector
{
public:
    size_t global_size; 
    size_t current_size;
    Data* data; 
    Vector() 
    {
        current_size = 0;
        global_size = 10;
        data = new int[global_size];
    }
    ~Vector()
    {
        delete[] data;

    }
};

Vector* vector_create()
{
    return new Vector;
}

void vector_delete(Vector* vector)
{
    //TODO: free vector internals
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    if (index <= vector->current_size)
    {
        return vector->data[index];
    }
    return (Data)0;
}

void vector_set(Vector* vector, size_t index, Data value)
{
    vector->data[index] = value;

}

size_t vector_size(const Vector* vector)
{
    return vector->current_size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (size <= vector->current_size)
    {
        vector->current_size = size;

        return;

    }
    if (size >= vector->global_size)
    {
        vector->global_size = size * 2;
        int* array_resize_inc = new int[vector->global_size];
        for (size_t i = 0; i < vector->current_size; i++)
        {
            array_resize_inc[i] = vector->data[i];
        }
        vector->current_size = size;
        delete[] vector->data;
        vector->data = array_resize_inc;
        return;
    }
    else
    {
        vector->current_size = size;
    }

}
