#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class Array {
public:
    Array() : data_(nullptr), size_(0) {}

    explicit Array(std::size_t size)
        : data_(size ? new T[size]() : nullptr), size_(size) {}

    Array(const Array& other)
        : data_(other.size_ ? new T[other.size_] : nullptr), size_(other.size_) {
        for (std::size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
    }

    Array(Array&& other) noexcept
        : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
    }

    Array& operator=(const Array& other) {
        if (this == &other) return *this;
        Array tmp(other);
        swap(tmp);
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
        return *this;
    }

    ~Array() { delete[] data_; }

    std::size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }

    T& operator[](std::size_t i) { return data_[i]; }
    const T& operator[](std::size_t i) const { return data_[i]; }

    T& at(std::size_t i) {
        if (i >= size_) throw std::out_of_range("Array::at");
        return data_[i];
    }
    const T& at(std::size_t i) const {
        if (i >= size_) throw std::out_of_range("Array::at");
        return data_[i];
    }

    T* begin() noexcept { return data_; }
    T* end() noexcept { return data_ + size_; }
    const T* begin() const noexcept { return data_; }
    const T* end() const noexcept { return data_ + size_; }

    void swap(Array& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }

private:
    T* data_;
    std::size_t size_;
};