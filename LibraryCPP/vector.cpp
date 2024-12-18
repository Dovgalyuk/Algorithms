#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector *vector = new Vector;
    vector->size = 0;
    vector->capacity = 8;
    vector->data = (Data*)malloc(vector->capacity * sizeof(Data));

    return vector;
}

void vector_delete(Vector *vector)
{
    free(vector->data);
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if(index < vector->size)
        return vector->data[index];
    
    return (Data)0;
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if(index < vector->size)
        vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if(size > vector->capacity)
    {
        while (vector->capacity < size)
            vector->capacity *= 2;

        vector->data = (Data*)realloc(vector->data, vector->capacity * sizeof(Data));
    }

    vector->size = size;
}
