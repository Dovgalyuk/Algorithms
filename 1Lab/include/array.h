#pragma once
#include <cstddef>

template <typename T>
class array
{
    T *data;
    size_t sz;

public:
    explicit array(size_t n) : data(new T[n]()), sz(n) {}
    ~array() { delete[] data; }
    T &operator[](size_t i) { return data[i]; }
    size_t size() const { return sz; }
};