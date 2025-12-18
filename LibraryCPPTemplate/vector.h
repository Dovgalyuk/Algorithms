#pragma once
#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>

template <typename Data>
class Vector {
private:
    Data* data;
    size_t currentSize;
    size_t currentCapacity;

    void reallocate(size_t newCapacity) {
        Data* newData = new Data[newCapacity];

        size_t elementsToCopy = std::min(currentSize, newCapacity);
        for (size_t i = 0; i < elementsToCopy; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        currentCapacity = newCapacity;
        currentSize = elementsToCopy;
    }

    void constructor(size_t size, const Data& initialValue) {
        if (size > 0) {
            data = new Data[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = initialValue;
            }
        }
        else {
            data = nullptr;
        }
    }

    void copy(const Vector& other) {
        if (other.currentCapacity > 0) {
            data = new Data[other.currentCapacity];
            for (size_t i = 0; i < other.currentSize; ++i) {
                data[i] = other.data[i];
            }
        }
        else {
            data = nullptr;
        }
    }


public:
    Vector() : data(nullptr), currentSize(0), currentCapacity(0) {}

    explicit Vector(size_t size) : currentSize(size), currentCapacity(size) {
        constructor(size, Data());
    }

    Vector(size_t size, const Data& initialValue)
        : currentSize(size), currentCapacity(size) {
        constructor(size, initialValue);
    }

    Vector(const Vector& other)
        : currentSize(other.currentSize), currentCapacity(other.currentCapacity) {
        copy(other);
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;

            currentSize = other.currentSize;
            currentCapacity = other.currentCapacity;

            copy(other);
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

    Data& operator[](size_t index) {
        if (index >= currentSize) {
            throw std::out_of_range("Vector index out of range");
        }
        return data[index];
    }

    const Data& operator[](size_t index) const {
        if (index >= currentSize) {
            throw std::out_of_range("Vector index out of range");
        }
        return data[index];
    }

    Data get(size_t index) const {
        return (*this)[index];
    }

    void set(size_t index, const Data& value) {
        (*this)[index] = value;
    }

    size_t size() const {
        return currentSize;
    }

    size_t capacity() const {
        return currentCapacity;
    }

    bool empty() const {
        return currentSize == 0;
    }

    void resize(size_t newSize) {
        if (newSize > currentCapacity) {
            size_t newCapacity = std::max(newSize, currentCapacity * 2);
            if (newCapacity == 0) newCapacity = 1;
            reallocate(newCapacity);
        }

        if (newSize > currentSize) {
            for (size_t i = currentSize; i < newSize; ++i) {
                data[i] = Data();
            }
        }

        currentSize = newSize;
    }

    void push_back(const Data& value) {
        if (currentSize >= currentCapacity) {
            size_t newCapacity = currentCapacity == 0 ? 1 : currentCapacity * 2;
            reallocate(newCapacity);
        }

        data[currentSize] = value;
        ++currentSize;
    }

    void pop_back() {
        if (currentSize > 0) {
            --currentSize;
        }
    }

    void clear() {
        currentSize = 0;
    }

    Data* begin() {
        return data;
    }

    Data* end() {
        return data + currentSize;
    }

    const Data* begin() const {
        return data;
    }

    const Data* end() const {
        return data + currentSize;
    }
};

#endif // VECTOR_TEMPLATE_H
