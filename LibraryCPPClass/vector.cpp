#include "vector.h"
#include <stdexcept>

template <typename T>
class Vector
{
public:
    Vector() : elements(nullptr), count(0), capacity(0) {}

    Vector(const Vector& a) : elements(nullptr), count(a.count), capacity(a.capacity)
    {
        if (capacity > 0)
        {
            elements = new Data[capacity];
            for (size_t i = 0; i < count; ++i)
                elements[i] = a.elements[i];
        }
    }

    Vector& operator=(const Vector& a)
    {
        if (this != &a)
        {
            delete[] elements;

            count = a.count;
            capacity = a.capacity;
            elements = new Data[capacity];
            for (size_t i = 0; i < count; ++i)
                elements[i] = a.elements[i];
        }
        return *this;
    }

    ~Vector()
    {
        delete[] elements;
    }

    Data get(size_t index) const
    {
        if (index >= count)
            throw std::out_of_range("Index out of range");
        return elements[index];
    }

    void set(size_t index, Data value)
    {
        if (index >= count)
            throw std::out_of_range("Index out of range");
        elements[index] = value;
    }

    size_t size() const
    {
        return count;
    }

    void resize(size_t size)
    {
        if (size > capacity)
        {
            capacity = size * 2;
            Data* newElements = new Data[capacity];
            for (size_t i = 0; i < count; ++i)
                newElements[i] = elements[i];
            delete[] elements;
            elements = newElements;
        }
        count = size;
    }

private:
    Data* elements;
    size_t count;
    size_t capacity;
};
