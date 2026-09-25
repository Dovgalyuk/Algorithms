#include "vector.h"

struct Vector
{
    Data *data;      // Указатель на динамический массив
    size_t size;     // Текущее количество элементов
    size_t capacity; // Выделенная ёмкость
};

Vector *vector_create()
{
    Vector *vector = new Vector;
    vector->data = nullptr;
    vector->size = 0;
    vector->capacity = 0;
    return vector;
    // return new Vector;
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
    if (vector)
    {
        delete[] vector->data;  // Освобождаем память массива
        delete vector;
    }
}

Data vector_get(const Vector *vector, size_t index)
{
    if (vector && index < vector->size)
    {
        return vector->data[index];
    }
    return (Data)0; // Значение по умолчанию при ошибке
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (vector && index < vector->size)
    {
        vector->data[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    if (vector)
    {
        return vector->size;
    }
    return 0;
}

void vector_resize(Vector *vector, size_t size)
{
    if (!vector)
        return;

    if (size == vector->size)
        return;

    // Если новая ёмкость больше текущей, увеличиваем
    if (size > vector->capacity)
    {
        size_t new_capacity = vector->capacity;
        if (new_capacity == 0)
            new_capacity = 1;

        // Увеличиваем ёмкость в 2 раза пока не хватит
        while (new_capacity < size)
        {
            new_capacity *= 2;
        }

        Data *new_data = new Data[new_capacity];

        // Копируем старые данные
        if (vector->data && vector->size > 0)
        {
            size_t copy_size = (vector->size < size) ? vector->size : size;
            for (size_t i = 0; i < copy_size; ++i)
            {
                new_data[i] = vector->data[i];
            }
        }

        // Инициализируем новые элементы нулями
        for (size_t i = vector->size; i < size; ++i)
        {
            new_data[i] = (Data)0;
        }

        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    else if (size < vector->size)
    {
        // Уменьшение размера - просто меняем size, ёмкость не трогаем
        // Элементы за пределами нового размера становятся недоступны
    }

    vector->size = size;
}
