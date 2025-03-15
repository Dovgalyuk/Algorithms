#include "vector.h"
#include <stdlib.h>

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;
};

Vector* vector_create()
{
    Vector* vector = new Vector;
    vector->data = nullptr;
    vector->size = 0;
    vector->capacity = 0;
    return vector;
}

void vector_delete(Vector* vector)
{
    free(vector->data);
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
    vector->data[index] = value;
}

size_t vector_size(const Vector* vector)
{
    return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (size > vector->capacity) 
    {
        vector->capacity = size * 2;
        vector->data = (Data*)realloc(vector->data, vector->capacity * sizeof(Data));
    }
    vector->size = size;
}