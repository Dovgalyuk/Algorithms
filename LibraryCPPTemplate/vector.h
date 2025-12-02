#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <algorithm>
#include <stdexcept>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector() : data(nullptr), sz(0), capacity(0)
    {
    }

    // copy constructor
    Vector(const Vector& a) : sz(a.sz), capacity(a.capacity)
    {
        if (capacity == 0) {
            data = nullptr;
        }
        else {
            data = new Data[capacity];
            std::copy(a.data, a.data + sz, data);
        }
    }

    // assignment operator
    Vector& operator=(const Vector& a)
    {
        if (this != &a) {
            delete[] data;
            sz = a.sz;
            capacity = a.capacity;
            if (capacity == 0) {
                data = nullptr;
            }
            else {
                data = new Data[capacity];
                std::copy(a.data, a.data + sz, data);
            }
        }
        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] data;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (index >= sz) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index >= sz) {
            throw std::out_of_range("Index out of bounds");
        }
        data[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return sz;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t new_size)
    {
        if (new_size > capacity) {
            size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
            while (new_capacity < new_size) {
                new_capacity *= 2;
            }
            Data* new_data = new Data[new_capacity];
            if (data) {
                std::copy(data, data + sz, new_data);
                delete[] data;
            }
            data = new_data;
            capacity = new_capacity;
        }
        sz = new_size;
    }

private:
    Data* data;
    size_t sz;
    size_t capacity;
};

#endif
