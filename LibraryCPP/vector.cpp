#include "vector.h"

struct Vector
{
    size_t size = 0;
    size_t capacity = 0;
    size_t curr_index = 0;
    Data* ptr = nullptr;
};

Vector* vector_create()
{
    return new Vector;
}

void vector_delete(Vector* vector)
{
    if (vector != nullptr)
    {
        if (vector->ptr)
            delete[] vector->ptr;
        delete vector;
    }
}

Data vector_get(const Vector* vector, size_t index)
{
    if (vector != nullptr && index <= vector->size)
    {
        return vector->ptr[index];
    }
    return (Data)0;
}

void vector_set(Vector* vector, size_t index, Data value)
{
    if (vector != nullptr && index <= vector->size)
    {
        vector->ptr[index] = value;
    }
}

size_t vector_size(const Vector* vector)
{
    if (vector != nullptr)
    {
        return vector->size;
    }
    return (size_t)0;
}

size_t vector_used_size(const Vector* vector) 
{ 
    if (vector != nullptr) 
    {
        return vector->curr_index;
    }
    return (size_t)0;
}

void vector_resize(Vector* vector, size_t new_size)
{
    if (new_size > vector->capacity)
    {
        size_t ncap = new_size * 2;
        Data* new_ptr = new Data[ncap];
        for (size_t i = 0; i < vector->size; ++i)
        {
            new_ptr[i] = vector->ptr[i];
        }

        delete[] vector->ptr;
        vector->ptr = new_ptr;
        vector->capacity = ncap;
    }
    vector->size = new_size;
}

Vector* vector_copy(const Vector* vector)
{
    if (vector != nullptr)
    {
        Vector* copy = new Vector;
        copy->size = vector->size;
        copy->capacity = vector->capacity;
        copy->ptr = new Data[copy->capacity];

        for (size_t i = 0; i < vector->size; ++i)
        {
            copy->ptr[i] = vector->ptr[i];
        }

        return copy;
    }
    return nullptr;
}

void vector_push(Vector* vector, Data value) {
    if (vector != nullptr) {

        if (vector->size >= vector->capacity) {
            vector_resize(vector, vector->size + 1);
        }

        vector_set(vector, vector->curr_index++, value);

        vector->size++;
    }
}