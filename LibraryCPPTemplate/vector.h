#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <iostream>

template <typename Data> class Vector
{
public:
    // Создает вектор
    Vector(): length(0), capacity(0), data(nullptr) // присв 0
    {
    }

    // Удаляет векторную структуру и внутренние данные
    ~Vector()
    {
        delete[] data;
    }

    // Извлекает элемент вектора с указанным индексом
    Data get(size_t index) const
    {
        return data[index];
    }

    // Задает элемент вектора с указанным индексом
    void set(size_t index, Data value)
    {
        data[index] = value;
    }

    // Получает текущий размер вектора
    size_t size() const
    {
        return length;
    }

    // копирование из 1 массива в другой
    void data_copy(Data* new_data, size_t size, size_t offset_old_data = 0, size_t offset_new_data = 0) {
        for (int i = 0; i < size; ++i) {
            new_data[offset_new_data + i] = data[offset_old_data + i];
        }
    }

    //увеличение вектора
    void expand_data(size_t size) {
        if (capacity >= size) // проверка на расширение
            return;
        if (capacity == 0)
            capacity = 1;
        while (capacity < size)
            capacity *= capacity_multiply;
    }

    // Изменяет размер вектора (может увеличиваться или уменьшаться)
    // В среднем должно быть O(1)
    void resize(size_t size)
    {
        if (capacity < size) {
            expand_data(size);
            Data* new_data = new Data[capacity];
            data_copy(new_data, this->size()); // копир из стар в нов массив
            delete[] data;
            data = new_data;
        }
        length = size;
    }

protected:
    size_t length;
    size_t capacity;
    const int capacity_multiply = 2;
    Data* data;
};

#endif