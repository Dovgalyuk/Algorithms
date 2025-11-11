#include "vector.h"

const size_t INCREASE_SIZE = 2;

struct Vector
{
    Data* arr;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector* vector = new Vector;

    vector->size = 0;
    vector->capacity = 1;
    vector->arr = new Data[vector->capacity]();

    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->arr;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if(index >= vector->size){
        return (Data)0;
    }

    return vector->arr[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if(index >= vector->size){
        return;
    }

    vector->arr[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if(size > vector->capacity)
    {
        size_t capacity = vector->capacity;

        while (size > capacity)
        {
            capacity *= INCREASE_SIZE;
        }

        Data* arr = new Data[capacity]();

        for(size_t i = 0; i < vector->size; i++)
        {
            arr[i] = vector->arr[i];
        }

        delete[] vector->arr;
        vector->arr = arr;
        vector->capacity = capacity;
    }
    
    vector->size = size;
}