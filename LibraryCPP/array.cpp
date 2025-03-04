#include "array.h"

template <typename T>
Array<T>::Array(size_t size) : size_(size), data(size) {}

template <typename T>
Array<T>::Array(const Array& other) : size_(other.size_), data(other.data) {}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        size_ = other.size_;
        data = other.data;
    }
    return *this;
}
template <typename T>
Array<T>::Array(Array&& other) noexcept : size_(other.size_), data(std::move(other.data)) {
    other.size_ = 0;
}

template <typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        size_ = other.size_;
        data = std::move(other.data);
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
size_t Array<T>::size() const {
    return size_;
}
template <typename T>
T& Array<T>::at(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T& Array<T>::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
T& Array<T>::operator[](size_t index) {
    return data[index];
}
template <typename T>
const T& Array<T>::operator[](size_t index) const {
    return data[index];
}

template <typename T>
void Array<T>::fill(const T& value) {
    std::fill(data.begin(), data.end(), value);
}

template class Array<int>;
