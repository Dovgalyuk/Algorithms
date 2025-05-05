#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

#include <cstddef>  // для size_t
#include <stdexcept>  // для std::out_of_range

template <typename Data>
class Array {
public:
    // Конструктор с заданием размера
    explicit Array(size_t size) : _size(size), _data(new Data[size]) {}

    // Конструктор копирования
    Array(const Array &a) : _size(a._size), _data(new Data[a._size]) {
        for (size_t i = 0; i < _size; ++i)
            _data[i] = a._data[i];
    }

    // Оператор присваивания
    Array &operator=(const Array &a) {
        if (this != &a) {
            delete[] _data;
            _size = a._size;
            _data = new Data[_size];
            for (size_t i = 0; i < _size; ++i)
                _data[i] = a._data[i];
        }
        return *this;
    }

    // Деструктор
    ~Array() {
        delete[] _data;
    }

    // Получить элемент по индексу
    Data get(size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return _data[index];
    }

    // Установить значение по индексу
    void set(size_t index, Data value) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        _data[index] = value;
    }

    // Вернуть размер массива
    size_t size() const {
        return _size;
    }

private:
    size_t _size = 0;
    Data* _data = nullptr;
};

#endif
