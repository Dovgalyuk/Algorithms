#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <string>
#include <stdexcept>

typedef std::string Data;

class Vector
{
public:
    Vector();

    Vector(const Vector &a);

    Vector &operator=(const Vector &a);

    ~Vector();

    Data get(size_t index) const;

    void set(size_t index, Data value);

    size_t size() const;

    void resize(size_t size);

    void push_back(Data value);

    void reverse();

private:
    Data* elements;
    size_t volume; // сколько памяти выделено
    size_t len; // сколько элементов реально используется

    void copy(const Vector &a);
};

#endif
