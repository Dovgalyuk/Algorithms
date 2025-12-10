#pragma once
#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename Data>
class Vector
{
public:
    // Creates vector
    Vector()
    {
        adata = nullptr;
        asize = 0;
        acapacity = 0;
    }

    // Creates vector with given size
    Vector(size_t size) : asize(size), acapacity(size) {
        if (size > 0) {
            adata = new Data[size];
            for (size_t i = 0; i < size; ++i) {
                adata[i] = Data();
            }
        }
        else {
            adata = nullptr;
        }
    }

    // Creates vector with given size and initial value
    Vector(size_t size, const Data& initial_value) : asize(size), acapacity(size) {
        if (size > 0) {
            adata = new Data[size];
            for (size_t i = 0; i < size; ++i) {
                adata[i] = initial_value;
            }
        }
        else {
            adata = nullptr;
        }
    }

    // copy constructor
    Vector(const Vector& a)
    {
        copyadata(a);
    }

    // assignment operator
    Vector& operator=(const Vector& a)
    {
        if (this != &a) {
            delete[] adata;
            copyadata(a);
        }
        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] adata;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (index < asize) {
            return adata[index];
        }
        else {
            throw std::out_of_range("Vector index out of range");
        }
    }

    // Sets vector element with the specified index
    void set(size_t index, const Data& value)
    {
        if (index < asize) {
            adata[index] = value;
        }
        else {
            throw std::out_of_range("Vector index out of range");
        }
    }

    // Access element by reference (for modification)
    Data& operator[](size_t index) {
        if (index < asize) {
            return adata[index];
        }
        else {
            throw std::out_of_range("Vector index out of range");
        }
    }

    // Access element by const reference (for reading)
    const Data& operator[](size_t index) const {
        if (index < asize) {
            return adata[index];
        }
        else {
            throw std::out_of_range("Vector index out of range");
        }
    }

    // Retrieves current vector size
    size_t size() const
    {
        return asize;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t size)
    {
        if (size <= acapacity) {
            asize = size;
        }
        else {
            size_t new_capacity = size * 2;
            Data* new_data = new Data[new_capacity];
            for (size_t i = 0; i < asize; i++) {
                new_data[i] = adata[i];
            }
            // Initialize new elements with default value
            for (size_t i = asize; i < size; i++) {
                new_data[i] = Data();
            }
            delete[] adata;
            adata = new_data;
            asize = size;
            acapacity = new_capacity;
        }
        return;
    }

private:
    // private data should be here
    Data* adata;
    size_t asize;
    size_t acapacity;
    void copyadata(const Vector& a)
    {
        if (a.size() > 0) {
            asize = a.size();
            acapacity = a.acapacity;
            Data* new_data = new Data[acapacity];
            for (size_t i = 0; i < asize; i++) {
                new_data[i] = a.get(i);
            }
            adata = new_data;
        }
        else {
            adata = nullptr;
            asize = 0;
            acapacity = 0;
        }
    }
};

#endif