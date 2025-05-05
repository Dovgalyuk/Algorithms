#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <algorithm>
#include <stdexcept>

template <typename Data>
class Vector
{
public:
    // Конструктор по умолчанию
    Vector() : vector_size(0), max_size(1), data(new Data[max_size]) {}

    // Конструктор копирования
    Vector(const Vector &a) : vector_size(a.vector_size), max_size(a.max_size), data(new Data[a.max_size])
    {
        std::copy(a.data, a.data + a.vector_size, data);
    }

    // Оператор присваивания
    Vector &operator=(const Vector &a)
    {
        if (this != &a)
        {
            delete[] data;
            vector_size = a.vector_size;
            max_size = a.max_size;
            data = new Data[max_size];
            std::copy(a.data, a.data + a.vector_size, data);
        }
        return *this;
    }

    // Конструктор перемещения
    Vector(Vector &&a) noexcept : vector_size(a.vector_size), max_size(a.max_size), data(a.data)
    {
        a.data = nullptr;
        a.vector_size = 0;
        a.max_size = 0;
    }

    // Оператор перемещения
    Vector &operator=(Vector &&a) noexcept
    {
        if (this != &a)
        {
            delete[] data;
            vector_size = a.vector_size;
            max_size = a.max_size;
            data = a.data;

            a.data = nullptr;
            a.vector_size = 0;
            a.max_size = 0;
        }
        return *this;
    }

    // Обмен содержимым двух векторов
    void swap(Vector &other) noexcept
    {
        std::swap(data, other.data);
        std::swap(vector_size, other.vector_size);
        std::swap(max_size, other.max_size);
    }

    // Деструктор
    ~Vector()
    {
        delete[] data;
    }

    // Получить элемент по индексу
    Data get(size_t index) const
    {
        if (index < vector_size)
            return data[index];
        else
            throw std::out_of_range("Index out of range");
    }

    // Установить элемент по индексу
    void set(size_t index, Data value)
    {
        if (index < vector_size)
            data[index] = value;
        else
            throw std::out_of_range("Index out of range");
    }

    // Получить текущий размер вектора
    size_t size() const
    {
        return vector_size;
    }

    // Изменить размер вектора
    void resize(size_t size)
    {
        if (size <= max_size)
        {
            vector_size = size;
            return;
        }

        // Увеличиваем размер вектора с учетом увеличения емкости в 2 раза
        size_t _max_size = std::max(size, max_size * 2);
        Data *new_data = new Data[_max_size];

        // Копируем старые данные в новый массив
        std::copy(data, data + vector_size, new_data);

        // Освобождаем старую память
        delete[] data;
        data = new_data;
        max_size = _max_size;
        vector_size = size;
    }

private:
    size_t vector_size; // размер вектора
    size_t max_size;    // максимальный размер вектора
    Data* data;         // указатель на данные вектора
};

#endif
