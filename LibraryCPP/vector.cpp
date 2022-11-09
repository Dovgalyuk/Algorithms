#include "vector.h"

struct Vector
{
    Data *data;
    size_t size;
    size_t max_size;

    Vector() {
        size = 0;
        max_size = 1;
        data = new Data[max_size];
    }

    ~Vector() {
        delete[] data;
    }
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    size_t size = vector->size;
    if(index < 0 || size <= index) {
        throw "Error: !"; 
    }
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    size_t size = vector->size;
    if(index < 0 || size <= index) {
        throw "Error: !";
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    size_t _size = vector->size;

    if (size <= vector->max_size) {
        vector->size = size;
        return;
    }
    // Выделение памяти под расширенный массив
    size_t _max_size = size *2;
    Data *tmp = new Data[_max_size];
    // Перенос элементов
    for(int i = 0; i < _size; i++) {
        tmp[i] = vector->data[i];
    }
    // Удаление текущего массива, замена расширенным
    delete[] vector->data;

    vector->data = tmp;
    vector->max_size = _max_size;
    vector->size = size;
}