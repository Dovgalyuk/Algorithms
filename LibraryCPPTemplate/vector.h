#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <limits>
#include <stdexcept>

// A simple dynamically sized array.
template <typename Data> class Vector
{
public:
    // Creates vector
    Vector() : elements(nullptr), length(0), capacity(0)
    {
    }

    // copy constructor
    Vector(const Vector &a)
        : elements(a.length ? new Data[a.length]{} : nullptr),
          length(a.length), capacity(a.length)
    {
        for (size_t i = 0; i < length; i++)
            elements[i] = a.elements[i];
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this != &a) {
            Data *newElements = a.length ? new Data[a.length]{} : nullptr;
            try {
                for (size_t i = 0; i < a.length; i++)
                    newElements[i] = a.elements[i];
            } catch (...) {
                delete[] newElements;
                throw;
            }

            delete[] elements;
            elements = newElements;
            length = a.length;
            capacity = a.length;
        }
        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] elements;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (index >= length)
            throw std::out_of_range("Vector index out of range");
        return elements[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index >= length)
            throw std::out_of_range("Vector index out of range");
        elements[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return length;
    }

    // Changes the vector size (may increase or decrease)
    // Amortized O(1) for increasing the size by one.
    void resize(size_t size)
    {
        if (size > capacity) {
            size_t newCapacity = capacity == 0 ? 4 : capacity;
            while (newCapacity < size) {
                if (newCapacity > std::numeric_limits<size_t>::max() / 2) {
                    newCapacity = size;
                    break;
                }
                newCapacity *= 2;
            }

            Data *newElements = new Data[newCapacity]{};
            try {
                for (size_t i = 0; i < length; i++)
                    newElements[i] = elements[i];
            } catch (...) {
                delete[] newElements;
                throw;
            }

            delete[] elements;
            elements = newElements;
            capacity = newCapacity;
        }

        // Newly added elements have default values, including after shrinking.
        for (size_t i = length; i < size; i++)
            elements[i] = Data();
        length = size;
    }

private:
    Data *elements;
    size_t length;
    size_t capacity;
};

#endif
