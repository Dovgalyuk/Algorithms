#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class Vector {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void reserve(std::size_t newCapacity)
    {
        if (newCapacity <= capacity_) {
            return;
        }

        T* newData = new T[newCapacity]();

        try {
            for (std::size_t i = 0; i < size_; ++i) {
                newData[i] = data_[i];
            }
        } catch (...) {
            delete[] newData;
            throw;
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

public:
    explicit Vector(std::size_t size = 0)
        : data_(size == 0 ? nullptr : new T[size]()),
          size_(size), capacity_(size)
    {
    }

    Vector(const Vector& other)
        : data_(other.capacity_ == 0
                    ? nullptr
                    : new T[other.capacity_]()),
          size_(other.size_), capacity_(other.capacity_)
    {
        try {
            for (std::size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        } catch (...) {
            delete[] data_;
            throw;
        }
    }

    Vector& operator=(const Vector& other)
    {
        if (this != &other) {
            Vector copy(other);

            std::swap(data_, copy.data_);
            std::swap(size_, copy.size_);
            std::swap(capacity_, copy.capacity_);
        }

        return *this;
    }

    ~Vector()
    {
        delete[] data_;
    }

    std::size_t size() const
    {
        return size_;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    void resize(std::size_t newSize)
    {
        if (newSize > capacity_) {
            std::size_t newCapacity =
                capacity_ == 0 ? 1 : capacity_;

            while (newCapacity < newSize) {
                if (newCapacity > static_cast<std::size_t>(-1) / 2) {
                    newCapacity = newSize;
                    break;
                }

                newCapacity *= 2;
            }

            reserve(newCapacity);
        }

        for (std::size_t i = newSize; i < size_; ++i) {
            data_[i] = T{};
        }

        size_ = newSize;
    }

    T& get(std::size_t index)
    {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }

        return data_[index];
    }

    const T& get(std::size_t index) const
    {
        if (index >= size_) {
            throw std::out_of_range("Vector index out of range");
        }

        return data_[index];
    }

    void set(std::size_t index, const T& value)
    {
        get(index) = value;
    }

    T& back()
    {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }

        return data_[size_ - 1];
    }

    const T& back() const
    {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }

        return data_[size_ - 1];
    }

    void push_back(const T& value)
    {
        T copy(value);

        if (size_ == static_cast<std::size_t>(-1)) {
            throw std::length_error("Vector size is too large");
        }

        resize(size_ + 1);
        data_[size_ - 1] = copy;
    }

    void pop_back()
    {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }

        resize(size_ - 1);
    }
};