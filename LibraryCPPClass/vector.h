#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

typedef int Data;

class Vector
{
public:
    Vector();
    Vector(const Vector& a);
    Vector& operator=(const Vector& a);
    ~Vector();
    Data get(size_t index) const;
    void set(size_t index, Data value);
    size_t size() const;
    void resize(size_t size);

private:
    Data* data_;
    size_t size_;
    size_t capacity_;
};

#endif
