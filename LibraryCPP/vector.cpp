#include "vector.h"
#include <cstdlib>  // для функции std::realloc

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;
};

Vector* vector_create()
{
    Vector* vector = new Vector;
    vector->size = 0;
    vector->capacity = 1;
    vector->data = (Data*)std::malloc(vector->capacity * sizeof(Data));
    return vector;
}

void vector_delete(Vector* vector)
{
    std::free(vector->data);
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    if (index < vector->size)
    {
        return vector->data[index];
    }
    return (Data)0;  // или выбросить исключение
}

void vector_set(Vector* vector, size_t index, Data value)
{
    if (index < vector->size)
    {
        vector->data[index] = value;
    }
    // можно добавить обработку ошибки если индекс вне диапазона
}

size_t vector_size(const Vector* vector)
{
    return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (size > vector->capacity)
    {
        size_t new_capacity = vector->capacity;
        while (new_capacity < size)
        {
            new_capacity *= 2;
        }
        vector->data = (Data*)std::realloc(vector->data, new_capacity * sizeof(Data));
        vector->capacity = new_capacity;
    }
    vector->size = size;
}