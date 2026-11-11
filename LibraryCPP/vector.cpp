#include "vector.h"

struct Vector
{
    size_t size;
    size_t capacity;
    Data* array;
};

Vector *vector_create()
{
    return new Vector{0, 2, new Data[2]};
}

void vector_delete(Vector *vector)
{
    delete[] vector->array;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->array[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    vector->array[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if(size > vector->capacity){
        while (size > vector->capacity)
        {
            vector->capacity *= 2;
        }

        Data* arrayNew = new Data[vector->capacity];

        for(size_t i = 0; i < vector->size; i++){
            arrayNew[i] = vector->array[i];
        }
        
        delete[] vector->array;
        vector->array = arrayNew;
    }
    
    vector->size = size;
}
