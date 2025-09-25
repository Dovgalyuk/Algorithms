#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

class Array {
public:
    explicit Array(std::size_t size);
    Array(const Array& a);
    Array& operator=(const Array& a);
    ~Array();

    std::size_t size() const;

    int& operator[](std::size_t index);
    const int& operator[](std::size_t index) const;

    int  get(std::size_t index) const;
    void set(std::size_t index, int value);

private:
    std::size_t _size;
    int* _data;
};

#endif
