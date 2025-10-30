#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>

template<typename T>
class Array {
public:
    explicit Array(size_t size) : size_(size), data_(size ? new T[size]() : nullptr) {}

    ~Array() {
        delete[] data_;
    }

    Array(const Array& other) : size_(other.size_), data_(size_ ? new T[size_] : nullptr) {
        if (data_) {
            std::copy(other.data_, other.data_ + size_, data_);
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            Array temp(other);
            std::swap(data_, temp.data_);
            std::swap(size_, temp.size_);
        }
        return *this;
    }

    size_t size() const noexcept { return size_; }

    void set(size_t index, const T& value) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        data_[index] = value;
    }

    const T& get(size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    T& operator[](size_t index) {
        return const_cast<T&>(static_cast<const Array&>(*this)[index]);
    }

    const T& operator[](size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

private:
    size_t size_ = 0;
    T* data_ = nullptr;
};

#endif // ARRAY_H