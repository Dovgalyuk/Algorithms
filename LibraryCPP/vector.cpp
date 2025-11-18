#include "vector.h"
#include <cstdlib>
#include <cstring>

struct Vector
{
    Data *data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector *vector = new Vector;
    vector->data = nullptr;
    vector->size = 0;
    vector->capacity = 0;
    return vector;
}

void vector_delete(Vector *vector)
{
    if (vector->data != nullptr)
    {
        delete[] vector->data;
    }
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size)
    {
        return (Data)0;
    }
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >= vector->size)
    {
        return;
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity)
    {
        // Вычисляем новую ёмкость: удваиваем, но не меньше требуемого размера
        size_t new_capacity = vector->capacity == 0 ? 1 : vector->capacity;
        while (new_capacity < size)
        {
            new_capacity *= 2;
        }
        
        // Выделяем память под новый массив
        Data *new_data = new Data[new_capacity];
        
        // Копируем старые данные в новый массив
        if (vector->data != nullptr)
        {
            for (size_t i = 0; i < vector->size; ++i)
            {
                new_data[i] = vector->data[i];
            }
            delete[] vector->data;
        }
        
        // Инициализируем новые элементы нулями
        for (size_t i = vector->size; i < size; ++i)
        {
            new_data[i] = (Data)0;
        }
        
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    else if (size < vector->size)
    {
        // Уменьшаем размер: просто обновляем размер, ёмкость оставляем прежней
        // Можно было бы уменьшить и ёмкость, если размер стал намного меньше, но это не обязательно
    }
    
    vector->size = size;
}
