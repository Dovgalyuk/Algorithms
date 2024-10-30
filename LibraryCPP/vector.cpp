#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
};

Vector *vector_create()
{
    Vector *vector = new Vector;
    vector->size = 0;
    vector->data = (Data*)malloc(vector->size);
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
    vector->data = (Data*)realloc(vector->data, size * sizeof(Data));
    if(size > vector->size)
    {
        for(size_t i = vector->size; i < size; i++)
        {
            vector->data[i] = (Data)0;
        }
    }
    vector->size = size;
}
