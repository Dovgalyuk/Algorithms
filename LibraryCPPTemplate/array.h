#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cmath>

template<typename T>
class Array {
private:
    T* data;
    size_t capacity;
    size_t current_size;

public:
    // Конструкторы
    explicit Array(size_t size = 0) : capacity(size), current_size(size) {
        data = new T[capacity];
        std::fill_n(data, capacity, T{});
    }

    Array(size_t size, const T& value) : capacity(size), current_size(size) {
        data = new T[capacity];
        std::fill_n(data, capacity, value);
    }

    // Конструктор копирования
    Array(const Array& other) : capacity(other.capacity), current_size(other.current_size) {
        data = new T[capacity];
        std::copy(other.data, other.data + current_size, data);
    }

    // Оператор присваивания
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            current_size = other.current_size;
            data = new T[capacity];
            std::copy(other.data, other.data + current_size, data);
        }
        return *this;
    }

    // Деструктор
    ~Array() {
        delete[] data;
    }

    // Доступ к элементам
    T& operator[](size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T& at(size_t index) {
        return operator[](index);
    }

    const T& at(size_t index) const {
        return operator[](index);
    }

    // Размер и емкость
    size_t size() const { return current_size; }
    size_t max_size() const { return capacity; }
    bool empty() const { return current_size == 0; }

    // Итераторы
    T* begin() { return data; }
    const T* begin() const { return data; }
    T* end() { return data + current_size; }
    const T* end() const { return data + current_size; }

    // Заполнение
    void fill(const T& value) {
        std::fill_n(data, current_size, value);
    }

    // Обмен
    void swap(Array& other) {
        std::swap(data, other.data);
        std::swap(capacity, other.capacity);
        std::swap(current_size, other.current_size);
    }

    // Операторы сравнения
    bool operator==(const Array& other) const {
        if (current_size != other.current_size) return false;
        return std::equal(begin(), end(), other.begin());
    }

    bool operator!=(const Array& other) const {
        return !(*this == other);
    }
};

#endif // ARRAY_H