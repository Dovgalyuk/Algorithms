#ifndef ARRAY_H
#define ARRAY_H

#include <vector> // Подключаем заголовочный файл для использования std::vector

using Data = int; // Используем псевдоним типа int для удобства

class Array
{
public:
    explicit Array(size_t size) : m_data(size) {} // Конструктор контейнера, принимающий размер массива и инициализирующий m_data с помощью конструктора std::vector

    Data get(size_t index) const // Метод для получения значения элемента по индексу
    {
        if (index < m_data.size()) { // Проверяем, что индекс не выходит за границы массива
            return m_data[index]; // Возвращаем значение элемента по индексу
        }
        return -1; // Возвращаем значение по умолчанию при некорректном индексе
    }

    void set(size_t index, Data value) // Метод для установки значения элемента по индексу
    {
        if (index < m_data.size()) { // Проверяем, что индекс не выходит за границы массива
            m_data[index] = value; // Устанавливаем значение элемента по индексу
        }
    }

    size_t size() const // Метод для получения размера массива
    {
        return m_data.size();
    }

private:
    std::vector<Data> m_data; // Внутренний контейнер, использующий std::vector для хранения данных
};

#endif