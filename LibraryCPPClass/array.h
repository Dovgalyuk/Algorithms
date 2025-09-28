#pragma once
#include <cstddef>

class Array {
public:
    explicit Array(std::size_t size = 0);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();

    std::size_t size() const;

    int  get(std::size_t index) const;
    void set(std::size_t index, int value);

private:
    std::size_t _size;
    int* _data;
};
