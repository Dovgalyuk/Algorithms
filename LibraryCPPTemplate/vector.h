#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>

template <typename Data>
class Vector {
public:
    Vector() : data(nullptr), _size(0), _capacity(0) {}

    Vector(const Vector& other) : _size(other._size), _capacity(other._size) {
        data = _capacity ? new Data[_capacity] : nullptr;
        for (size_t i = 0; i < _size; ++i) {
            data[i] = other.data[i];
        }
    }

    Vector(Vector&& other) noexcept 
        : data(other.data), _size(other._size), _capacity(other._capacity) {
        other.data = nullptr;
        other._size = other._capacity = 0;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            _size = other._size;
            _capacity = other._capacity;
            other.data = nullptr;
            other._size = other._capacity = 0;
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
    }

    void swap(Vector& other) noexcept {
        std::swap(data, other.data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
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
    size_t capacity() const { return _capacity; }
    bool empty() const { return _size == 0; }

    void resize(size_t new_size) {
        if (new_size > _capacity) {
            reserve(new_size);
        }
        for (size_t i = _size; i < new_size; ++i) {
            data[i] = Data(); 
        }
        _size = new_size;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > _capacity) {
            Data* new_data = new Data[new_capacity];
            for (size_t i = 0; i < _size; ++i) {
                new_data[i] = std::move(data[i]);
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
        data[_size] = value;
        ++_size;
    }

    void push_back(Data&& value) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        data[_size] = std::move(value);
        ++_size;
    }

    void erase(size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < _size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --_size;
        data[_size].~Data();
    }

    void clear() {
        delete[] data;
        data = nullptr;
        _size = _capacity = 0;
    }

private:
    Data* data;
    size_t _size;
    size_t _capacity;
};

#endif // VECTOR_TEMPLATE_H
