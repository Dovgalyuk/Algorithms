#include <stdlib.h>
#include "vector.h"


typedef struct Vector
{
    size_t size;
    size_t capacity;
    Data* array;
    FFree* destruct;
    Data filler;
} Vector;

Vector *vector_create(FFree* f, Data user_filler)
{
    Vector* vector = malloc(sizeof(Vector));
    vector->size = 0;
    vector->capacity = 4;
    vector->array = (Data*) malloc(sizeof(Data)*vector->capacity);
    vector->destruct = f;
    vector->filler = user_filler;
    return vector;
}

void vector_delete(Vector *vector)
{
    if (vector->destruct != NULL)
        for (size_t i = 0; i < vector_size(vector); i++)
            vector->destruct((void*) vector->array[i]);
    
    free(vector->array);
    free(vector);
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index < vector_size(vector))
        return vector->array[index];
    else
        return vector->filler;
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index < vector_size(vector))
        vector->array[index] = value;
    else
    {
        vector_resize(vector, index + 1);
        vector->array[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (vector->capacity < size)
    {
        size_t new_capacity = vector->capacity;
        if (new_capacity == 0)
                new_capacity = 4;
        while (new_capacity < size)
            new_capacity *= 2;
        
        vector->array = (Data*) realloc(vector->array, new_capacity * sizeof(Data));
        vector->capacity = new_capacity;
        for (size_t i = vector->size; i < size; i++)
                vector->array[i] = vector->filler;
    }
    else if (size < vector->size)
    {
        if (vector->destruct != NULL)
        {
            for (size_t i = size; i < vector->size; i++)
            {
                if (vector->array[i] != vector->filler)
                    vector->destruct((void*) vector->array[i]);
            }
        }
        vector->array = (Data*) realloc(vector->array, size+1 * sizeof(Data));
        vector->capacity = size;
    } 
    vector->size = size;
}
