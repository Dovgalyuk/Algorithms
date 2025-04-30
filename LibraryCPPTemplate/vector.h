#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <algorithm> 

template <typename Data>
class Vector {
public:

    Vector() : data(nullptr), capacity(0), currentSize(0) {}

    Vector(size_t size, const Data& defaultValue) : data(nullptr), capacity(0), currentSize(0) {
        resize(size);
        for (size_t i = 0; i < size; ++i) {
            data[i] = defaultValue;
        }
    }

    Vector(const Vector &other) : data(nullptr), capacity(0), currentSize(0) {
        resize(other.currentSize);
        std::copy(other.data, other.data + other.currentSize, data);
    }

    Vector &operator=(const Vector &other) {
        if (this != &other) {
            delete[] data;
            data = nullptr;
            capacity = 0;
            currentSize = 0;
            resize(other.currentSize);
            std::copy(other.data, other.data + other.currentSize, data);
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

    Data& get(size_t index) {
        if (index >= currentSize) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        return data[index]; 
    }

    const Data& get(size_t index) const {
        if (index >= currentSize) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        return data[index]; 
    }

    // Установка элемента по индексу
    void set(size_t index, Data value) {
        if (index >= currentSize) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        data[index] = value;
    }

    // Текущий размер вектора
    size_t size() const {
        return currentSize;
    }

    // Изменение размера вектора
    void resize(size_t newSize) {
        if (newSize > capacity) {
            size_t newCapacity = std::max(newSize, capacity * 2);
            Data *newData = new Data[newCapacity];
            if (data) {
                std::copy(data, data + currentSize, newData);
                delete[] data;
            }
            data = newData;
            capacity = newCapacity;
        }
        currentSize = newSize;
    }

private:
    Data *data;          
    size_t capacity;     
    size_t currentSize;  
};

#endif
