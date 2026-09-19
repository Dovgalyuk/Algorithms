#include "vector.h"

Vector::Vector()
{
}

Vector::Vector(const Vector &a)
{
}

Vector &Vector::operator=(const Vector &a)
{
    return *this;
}

Vector::~Vector()
{
}

Data Vector::get(size_t index) const
{
    return Data();
}

void Vector::set(size_t index, Data value)
{
}

size_t Vector::size() const
{
    return 0;
}

void Vector::resize(size_t size)
{
}
