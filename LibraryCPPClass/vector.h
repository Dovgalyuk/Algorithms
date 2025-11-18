#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <stdexcept>

typedef int Data;

class Vector {
    Data* data;      
    size_t sz;       
    size_t cap;      

public:
    Vector();
    Vector(const Vector& a);
    Vector& operator=(const Vector& a);
    ~Vector();

    Data get(size_t index) const;
    void set(size_t index, Data value);
    size_t size() const;
    void resize(size_t newSize);
};

#endif
