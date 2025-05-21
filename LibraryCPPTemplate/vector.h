#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>

template <typename Data>
class Vector {
public:
    Vector() : data(nullptr), _size(0), _capacity(0) {}

    Vector(const Vector& other) : _size(other._size), _capacity(other._size) {
        data = new Data[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            data[i] = other.data[i];
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            _size = other._size;
            _capacity = other._size;
            data = new Data[_capacity];
            for (size_t i = 0; i < _size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

    Data& operator[](size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    const Data& operator[](size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    Data get(size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return data[index];
    }

    void set(size_t index, const Data& value) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        data[index] = value;
    }

    size_t size() const { return _size; }

    void resize(size_t new_size) {
        if (new_size > _capacity) {
            reserve(new_size * 2);
        }
        _size = new_size;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > _capacity) {
            Data* new_data = new Data[new_capacity];
            for (size_t i = 0; i < _size; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            _capacity = new_capacity;
        }
    }

    void push_back(const Data& value) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        data[_size++] = value;
    }

    void erase(size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < _size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --_size;
    }

private:
    Data* data;
    size_t _size;
    size_t _capacity;
};

#endif // VECTOR_TEMPLATE_H
