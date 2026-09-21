#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

template <typename Data>
class Array
{
private:
    Data* data;
    size_t array_size;

public:

    // создание массива заданного размера
    Array(size_t size)
    {
        array_size = size;
        data = new Data[array_size];
    }


    // конструктор копирования
    Array(const Array& other)
    {
        array_size = other.array_size;
        data = new Data[array_size];

        for (size_t i = 0; i < array_size; i++)
        {
            data[i] = other.data[i];
        }
    }


    // оператор присваивания
    Array& operator=(const Array& other)
    {
        if (this != &other)
        {
            delete[] data;

            array_size = other.array_size;
            data = new Data[array_size];

            for (size_t i = 0; i < array_size; i++)
            {
                data[i] = other.data[i];
            }
        }

        return *this;
    }


    // освобождение памяти
    ~Array()
    {
        delete[] data;
    }


    // получить элемент
    Data get(size_t index) const
    {
        return data[index];
    }


    // изменить элемент
    void set(size_t index, Data value)
    {
        data[index] = value;
    }


    // получить размер
    size_t size() const
    {
        return array_size;
    }
};

#endif
