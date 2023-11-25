#include "vector.h"

struct Vector
{
    Data* arr;
    
    Data current_size;
    Data global_size;

    Vector()
    {
        current_size = 0;
        global_size = 10;

        arr = new Data[global_size];
    }
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->arr;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index <= vector->current_size)
        return vector->arr[index];
    else
        return (Data)0;
}

void vector_set(Vector *vector, size_t index, Data value)
{
    vector->arr[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->current_size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size <= vector->current_size)
    {
        vector->current_size = size;

        return;
    }
    else
        vector->current_size = size;
    
    if (size >= vector->global_size)
    {
        vector->global_size = size * 2;

        Data* arr_temp = new Data[vector->global_size];
        
        for (size_t i = 0; i < vector->current_size; i++)
            arr_temp[i] = vector->arr[i];

        delete[] vector->arr;

        vector->arr = arr_temp;
        vector->current_size = size;
    }
}