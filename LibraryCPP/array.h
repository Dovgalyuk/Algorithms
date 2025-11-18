#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

using Data = int; 

class Array {
public:
    Array(size_t size);
    Array(const Array& a);
    Array& operator=(const Array& a);
    ~Array();

    Data get(size_t index) const;
    void set(size_t index, Data value);
    size_t size() const;

private:
    Data* data;
    size_t sz;
    size_t cap;
};

#endif 
