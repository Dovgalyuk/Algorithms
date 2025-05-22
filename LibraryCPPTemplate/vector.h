#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>

template <typename Data>
class Vector {
public:
    Vector() noexcept : data(nullptr), _size(0), _capacity(0) {}

    Vector(const Vector& other) : _size(other._size), _capacity(other._size) {
        data = _capacity ? new Data[_capacity] : nullptr;
        try {
            for (size_t i = 0; i < _size; ++i) {
                data[i] = other.data[i];
            }
        } catch (...) {
            delete[] data;
            throw;
        }
    }

    Vector(Vector&& other) noexcept 
        : data(other.data), _size(other._size), _capacity(other._capacity) {
        other.data = nullptr;
        other._size = other._capacity = 0;
    }

    ~Vector() {
        clear();
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
            clear();
            swap(other);
        }
        return *this;
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

    size_t size() const noexcept { return _size; }
    size_t capacity() const noexcept { return _capacity; }
    bool empty() const noexcept { return _size == 0; }

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
        if (new_capacity <= _capacity) return;
        
        Data* new_data = new Data[new_capacity]; 
        try {
            for (size_t i = 0; i < _size; ++i) {
                new_data[i] = std::move(data[i]); 
            }
        } catch (...) {
            delete[] new_data;
            throw;
        }
        
        delete[] data;
        data = new_data;
        _capacity = new_capacity;
    }

    void push_back(const Data& value) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        data[_size++] = value;
    }

    void push_back(Data&& value) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        data[_size++] = std::move(value);
    }

    void clear() noexcept {
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
