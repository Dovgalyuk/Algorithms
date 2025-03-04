#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Array {
private:
    T* data;
    size_t size;

public:
    Array(size_t size) : size(size) {
        if (size == 0) {
            data = nullptr;
        } else {
            data = new T[size];
        }
    }

    Array(const Array& other) : size(other.size) {
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;

            size = other.size;
            data = new T[size];

            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Array(Array&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;

            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }

    ~Array() {
        delete[] data;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за границы массива");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за границы массива");
        }
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    void set(size_t index, const T& value) {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за границы массива");
        }
        data[index] = value;
    }

    T get(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за границы массива");
        }
        return data[index];
    }
};

#endif
