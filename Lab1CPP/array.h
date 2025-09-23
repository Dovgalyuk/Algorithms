#pragma once

#include <cstddef>

class Array {
public:
    explicit Array(size_t size);
    Array(const Array& a);
    Array& operator=(const Array& a);
    ~Array();

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    size_t size() const;

private:
    size_t _size;
    int* _data;
};
