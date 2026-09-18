#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstddef>
#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    T* data;
    std::size_t size;

public:
    explicit DynamicArray(std::size_t n) : data(nullptr), size(n) {
        if (n == 0) {
            throw std::invalid_argument("Размер массива должен быть больше 0");
        }

        data = new T[size];
    }

    DynamicArray(const DynamicArray& other)
        : data(new T[other.size]), size(other.size) {

        for (std::size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    T& operator[](std::size_t index) {
        if (index >= size) {
            throw std::out_of_range("Выход за границы массива");
        }

        return data[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Выход за границы массива");
        }

        return data[index];
    }

    std::size_t getSize() const {
        return size;
    }
};

#endif
