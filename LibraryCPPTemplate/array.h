#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename Data>
class Array{
private:
    Data* data;
   std::size_t count;

    void copyData(const Array& a){
        for (std::size_t i =0; i < count;i++){
            data[i]=a.data[i];
        }
    }

public:
    // Создание массива заданного размера
   explicit Array(std::size_t size)
    {
        count = size;
        data = new Data[count];
    }

    // Создание копии массива
    Array(const Array& a)
        
    {
        count = a.count;
        data = new Data[count];
        
        copyData(a);

    }

    // Копирование элементов без изменения размера
    Array& operator=(const Array& a)
    {
        if (this == &a)
        {
            return *this;
        }

        if (count != a.count)
        {
            throw std::invalid_argument("Разные размеры массивов");
        }

        copyData(a);

        return *this;
    }

    // Освобождение памяти
    ~Array()
    {
        delete[] data;
    }

    // Получение элемента
    Data get(size_t index) const
    {
        if (index >= count)
        {
            throw std::out_of_range("Неправильный индекс");
        }

        return data[index];
    }

    // Изменение элемента
    void set(size_t index, const Data& value)
    {
        if (index >= count)
        {
            throw std::out_of_range("Неправильный индекс");
        }

        data[index] = value;
    }

    // Получение размера массива
    size_t size() const
    {
        return count;
    }
};

#endif