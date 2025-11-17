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
        : m_data(nullptr), m_size(0), m_capacity(0)
    { }

    // copy constructor
    Vector(const Vector &a) 
        : m_data(nullptr), m_size(a.m_size), m_capacity(a.m_capacity)
    {
        if (m_capacity > 0) {
            m_data = new Data[m_capacity];
        }
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = a.m_data[i];
        }
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this == &a) {
            return *this;
        }

        delete[] m_data;

        m_size = a.m_size;
        m_capacity = a.m_capacity;
        m_data = m_capacity > 0 ? new Data[m_capacity] : nullptr;

        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = a.m_data[i];
        }

        return *this;
    }

    // Deletes vector structure and internal data
    ~Vector()
    {
        delete[] m_data;
    }

    // Retrieves vector element with the specified index
    Data get(size_t index) const
    {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        return m_data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        m_data[index] = value;
    }

    // Retrieves current vector size
    size_t size() const
    {
        return m_size;
    }

    // Changes the vector size (may increase or decrease)
    // Should be O(1) on average
    void resize(size_t newm_size)
    {
        if (newm_size <= m_capacity) {
            m_size = newm_size;
            return;
        }

        size_t newm_capacity = m_capacity == 0 ? 1 : m_capacity;
        while (newm_capacity < newm_size) {
            newm_capacity *= 2;
        }

        Data *newm_data = new Data[newm_capacity];

        for (size_t i = 0; i < m_size; ++i) {
            newm_data[i] = m_data[i];
        }

        delete[] m_data;

        m_data = newm_data;
        m_capacity = newm_capacity;
        m_size = newm_size;
    }

private:
    // private data should be here
    Data *m_data;
    size_t m_size;
    size_t m_capacity;
};

#endif
