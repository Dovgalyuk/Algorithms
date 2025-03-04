#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class Array{
private:
    std::vector<T> data;
    size_t size_;
public:
    Array(size_t size) : data(size), size_(size) {}

    Array(const Array& other) : data(other.data), size_(other.size_) {}

    Array& operator=(const Array& other) {
        if (this != &other) {
            data = other.data;
            size_ = other.size_;
        }
        return *this;
    }

    Array(Array&& other) noexcept : data(std::move(other.data)), size_(other.size_) {
        other.size_ = 0;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }

    size_t size() const {
        return size_;
    }

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    void fill(const T& value) {
        std::fill(data.begin(), data.end(), value);
    }
};

#endif
