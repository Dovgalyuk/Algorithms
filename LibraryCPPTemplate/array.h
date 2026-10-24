#pragma once
#include <utility>
#include <cstddef>
#include <stdexcept>

template <typename T>
class Array {
private:
    T* data_;
    std::size_t size_;

public:
    explicit Array(std::size_t size)
        : data_(nullptr), size_(size)
    {
        if (size_ > 0) {
            data_ = new T[size_];
        }
    }

    Array(const Array& other)
        : data_(nullptr), size_(other.size_)
    {
        if (size_ > 0) {
            data_ = new T[size_];

            for (std::size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    Array& operator=(const Array& other)
    {
        if (this == &other) {
            return *this;
        }

        Array copy(other);

        std::swap(data_, copy.data_);
        std::swap(size_, copy.size_);

        return *this;
    }

    ~Array()
    {
        delete[] data_;
    }

    std::size_t size() const
    {
        return size_;
    }

    T get(std::size_t index) const
    {
        if (index >= size_) {
            throw std::out_of_range("Array index is out of range");
        }

        return data_[index];
    }

    void set(std::size_t index, const T& value)
    {
        if (index >= size_) {
            throw std::out_of_range("Array index is out of range");
        }

        data_[index] = value;
    }
};