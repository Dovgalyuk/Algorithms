#include "vector.h"

struct Vector
{
    size_t size;
    size_t capacity;
    Data* pointer;
    Vector()
    {
        size = 0;
        capacity = 0;
        pointer = nullptr;
    }
    ~Vector()
    {
        delete[] pointer;
        pointer = nullptr;
    }
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->pointer[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    vector->pointer[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size == vector->size) return;
    else if (size > vector->size)
    {
        if (size > vector->capacity)
        {
            if (size < 5) vector->capacity = size;
            else vector->capacity = size + ((size - 3) / 2);
            int* ptr = new int[vector->capacity]();
            for (int i = 0; i < vector->size; i++)
                ptr[i] = vector->pointer[i];
            vector->size = size;
            delete[] vector->pointer;
            vector->pointer = ptr;
        }
        else vector->size = size;
    }
    else vector->size = size;
}
