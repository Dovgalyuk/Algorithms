#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <limits>

template <typename Data>
class Vector {
public:
    Vector() noexcept : data(nullptr), _size(0), _capacity(0) {}

    Vector(const Vector& other) : _size(other._size), _capacity(other._size) {
        if (_capacity > 0) {
            data = static_cast<Data*>(::operator new(_capacity * sizeof(Data)));
            for (size_t i = 0; i < _size; ++i) {
                new (&data[i]) Data(other.data[i]);
            }
        } else {
            data = nullptr;
        }
    }

    Vector(Vector&& other) noexcept 
        : data(other.data), _size(other._size), _capacity(other._capacity) {
        other.data = nullptr;
        other._size = other._capacity = 0;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector tmp(other);
            swap(tmp);
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

    ~Vector() {
        clear();
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
        
        if (new_size > _size) {
            for (size_t i = _size; i < new_size; ++i) {
                new (&data[i]) Data();
            }
        } else if (new_size < _size) {
            for (size_t i = new_size; i < _size; ++i) {
                data[i].~Data();
            }
        }
        _size = new_size;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity <= _capacity) return;
        
        if (new_capacity > max_size()) {
            throw std::length_error("Vector capacity exceeded");
        }
        
        Data* new_data = static_cast<Data*>(::operator new(new_capacity * sizeof(Data)));
        for (size_t i = 0; i < _size; ++i) {
            new (&new_data[i]) Data(std::move(data[i]));
            data[i].~Data();
        }
        
        ::operator delete(data);
        data = new_data;
        _capacity = new_capacity;
    }

    void push_back(const Data& value) {
        if (_size == _capacity) {
            reserve(calculate_growth());
        }
        new (&data[_size]) Data(value);
        ++_size;
    }

    void push_back(Data&& value) {
        if (_size == _capacity) {
            reserve(calculate_growth());
        }
        new (&data[_size]) Data(std::move(value));
        ++_size;
    }

    void erase(size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        
        data[index].~Data();
        for (size_t i = index; i < _size - 1; ++i) {
            new (&data[i]) Data(std::move(data[i + 1]));
            data[i + 1].~Data();
        }
        --_size;
    }

    void clear() noexcept {
        if (data) {
            for (size_t i = 0; i < _size; ++i) {
                data[i].~Data();
            }
            ::operator delete(data);
            data = nullptr;
            _size = _capacity = 0;
        }
    }

    size_t max_size() const noexcept {
        return std::numeric_limits<size_t>::max() / sizeof(Data);
    }

private:
    Data* data;
    size_t _size;
    size_t _capacity;

    size_t calculate_growth() const {
        const size_t geometric = _capacity * 2;
        if (geometric < _capacity) {
            return max_size();
        }
        return geometric;
    }
};

#endif // VECTOR_TEMPLATE_H
