#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector() : elements(nullptr), capacity_value(0), size_value(0)
    {
    }

    // copy constructor
    Vector(const Vector &a) : capacity_value(a.capacity_value), size_value(a.size_value)
    {
        copyFunc(a);
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this != &a) {
            delete[] elements;
            capacity_value = a.capacity_value;
            size_value = a.size_value;
            copyFunc(a);
        }
        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] elements;
    }

    // Retrieves vector element with the specified index
    Data& get(size_t index)
    {
        if (index >= size_value) {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }
    const Data& get(size_t index) const
    {
        if (index >= size_value) {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index >= size_value) {
            throw std::out_of_range("Index out of range");
        }
        elements[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return size_value;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (size > capacity_value) {
            size_t new_capacity = 1;
            if (capacity_value != 0) {
                new_capacity = capacity_value;
            }
            while (new_capacity < size) {
                new_capacity *= 2;
            }

            Data* new_data = new Data[new_capacity];
            for (size_t i = 0; i < size_value; ++i) {
                new_data[i] = elements[i];
            }
            delete[] elements;
            elements = new_data;
            capacity_value = new_capacity;
        }
        size_value = size;
    }

private:
    // private data should be here
    void copyFunc(const Vector& a)
    {
        if (capacity_value > 0) {
            elements = new Data[capacity_value];
            for (size_t i = 0; i < size_value; ++i) {
                elements[i] = a.elements[i];
            }
        }
        else {
            elements = nullptr;
        }
    }
    Data* elements;
    size_t capacity_value;
    size_t size_value;
};

#endif
