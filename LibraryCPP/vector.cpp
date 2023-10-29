#include "vector.h"

struct Vector
{
public:
    size_t global_size; //Глобальный размер
    size_t current_size; //Текущий размер
    Data* data; //Данные
    Vector() //Конструктор
    {
        current_size = 0;
        global_size = 10;
        data = new int[global_size];
    }
    ~Vector() //Деструктор
    {
        delete[] data;
    }
};

Vector* vector_create()
{
    return new Vector;
}

void vector_delete(Vector* vector)
{
    // TODO: free vector internals
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    if (index <= vector->current_size)
    {
        return vector->data[index];
    }
    return (Data)0;
}

void vector_set(Vector* vector, size_t index, Data value)
{
    if (vector->current_size == vector->global_size)
    {
        vector_resize(vector, vector->current_size);
    }

    vector->data[index] = value;
    vector->current_size++;
}

size_t vector_size(const Vector* vector)
{
    return vector->current_size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (size <= vector->current_size)  //Уменьшение размера вектора при удалении элемента
    {
        vector->current_size -= size;
        int* array_resize_dec = new int[vector->current_size];
        for (size_t i = 0; i < vector->current_size; i++)
        {
            array_resize_dec[i] = vector->data[i];
        }
        vector->data = array_resize_dec;
        return;
    }

    vector->global_size *= 2;                      //Увеличение размера вектора при добавлении элемента 
    int* array_resize_inc = new int[vector->global_size];

    for (size_t i = 0; i < vector->current_size; i++)
    {
        array_resize_inc[i] = vector->data[i];
    }
    vector->data = array_resize_inc;
    delete[] array_resize_inc;
}