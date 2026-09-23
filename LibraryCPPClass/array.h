#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

typedef int Data;

class Array
{
public:
    Array(size_t size);
    ~Array();
    Data get(size_t index) const;
    void set(size_t index, Data value);
    size_t size() const;

private:
    Data* data_;
    size_t size_;
};

#endif
