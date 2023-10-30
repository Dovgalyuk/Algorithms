#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

template <typename Data>
class Vector
{
public:
    Vector()  // Конструктор по умолчанию
    {
        vector_size = 0;  // Изначальный размер вектора - 0
        max_size = 1;  // Максимальный размер вектора - 1
        data = new Data[max_size];  // Выделение памяти под один элемент
    }

    Vector(const Vector& other)  // Конструктор копирования
        : data(new Data[other.max_size]), vector_size(other.vector_size), max_size(other.max_size)
    {
        for (size_t i = 0; i < vector_size; i++)  // Копирование данных из другого вектора
        {
            data[i] = other.data[i];
        }
    }

    Vector& operator=(const Vector& other)  // Оператор присваивания
    {
        if (this == &other) // Проверка на самоприсваивание
        {
            return *this;
        }

        delete[] data;  // Освобождение текущих данных

        vector_size = other.vector_size;  // Копирование размера вектора
        max_size = other.max_size;  // Копирование максимального размера
        data = new Data[max_size];  // Выделение новой памяти

        for (size_t i = 0; i < vector_size; i++)  // Копирование данных из другого вектора
        {
            data[i] = other.data[i];
        }

        return *this;  // Возвращаем ссылку на текущий объект
    }

    ~Vector()  // Деструктор
    {
        delete[] data;  // Освобождение памяти
    }

    Data get(size_t index) const  // Получение элемента по индексу
    {
        if (index < vector_size)  // Если индекс допустимый
            return data[index];  // Возвращаем элемент
        else
            throw std::out_of_range("Index out of range");  // Если нет, выбрасываем исключение
    }

    void set(size_t index, Data value)  // Установка значения по индексу
    {
        if (index < vector_size)  // Если индекс допустимый
            data[index] = value;  // Устанавливаем значение
        else
            throw std::out_of_range("Index out of range");  // Если нет, выбрасываем исключение
    }

    size_t size() const  // Получение текущего размера вектора
    {
        return vector_size;
    }

    void resize(size_t size)  // Изменение размера вектора
    {
        if (size <= max_size)  // Если новый размер меньше максимального
        {
            vector_size = size;  // Устанавливаем новый размер
            return;
        }

        size_t _max_size = size * 2;  // Вычисляем новый максимальный размер
        Data* new_data = new Data[_max_size];  // Выделяем новую память

        for (size_t i = 0; i < vector_size; i++)  // Копируем старые данные
        {
            new_data[i] = data[i];
        }

        delete[] data;  // Освобождаем старую память
        data = new_data;  // Присваиваем указатель на новую память
        max_size = _max_size;  // Обновляем максимальный размер
        vector_size = size;  // Обновляем текущий размер
    }

private:
    Data* data;  // Указатель на данные
    size_t vector_size;  // Текущий размер вектора
    size_t max_size;  // Максимальный размер вектора
};


#endif