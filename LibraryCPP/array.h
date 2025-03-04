#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Array{
private:
    std::vector<T> data;
    size_t size_;
public:
    Array(size_t size);
    Array(const FixedArray& other);
    Array& operator=(const Array& other);
    Array(Array&& other) noexcept;
    Array& operator=(Array&& other) noexcept;

    size_t size() const;
    T& at(size_t index);
    const T& at(size_t index) const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void fill(const T& value);
};

#endif
