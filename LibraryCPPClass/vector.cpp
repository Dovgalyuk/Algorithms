#include "vector.h"
#include <stdexcept>

Vector::Vector()
    : data(nullptr), sz(0), cap(0)
{
}

Vector::Vector(const Vector& a)
    : data(nullptr), sz(a.sz), cap(a.cap)
{
    if (cap > 0) {
        data = new Data[cap];
        for (size_t i = 0; i < sz; i++)
            data[i] = a.data[i];
    }
}

Vector& Vector::operator=(const Vector& a)
{
    if (this != &a) {
        delete[] data;
        sz = a.sz;
        cap = a.cap;
        data = nullptr;
        if (cap > 0) {
            data = new Data[cap];
            for (size_t i = 0; i < sz; i++)
                data[i] = a.data[i];
        }
    }
    return *this;
}

Vector::~Vector()
{
    delete[] data;
}

Data Vector::get(size_t index) const
{
    if (index >= sz) throw std::out_of_range("vector_get out of range");
    return data[index];
}

void Vector::set(size_t index, Data value)
{
    if (index >= sz) throw std::out_of_range("vector_set out of range");
    data[index] = value;
}

size_t Vector::size() const
{
    return sz;
}

void Vector::resize(size_t newSize)
{
    if (newSize > cap) {
        size_t newcap = cap ? cap * 2 : 4;
        while (newcap < newSize) newcap *= 2;

        Data* newdata = new Data[newcap];
        for (size_t i = 0; i < sz; i++)
            newdata[i] = data[i];

        delete[] data;
        data = newdata;
        cap = newcap;
    }
    sz = newSize;
}

