#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename Data> class Vector
{
public:
    // Creates vector
    Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

    // copy constructor
    Vector(const Vector &a) : m_data(nullptr), m_size(0), m_capacity(0)
    {
        copy_from(a);
    }

    // assignment operator
    Vector &operator=(const Vector &a)
    {
        if (this != &a)
        {
            delete[] m_data;
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;

            copy_from(a);
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
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }
        return m_data[index];
    }

    // Sets vector element with the specified index
    void set(size_t index, Data value)
    {
        if (index >= m_size)
        {
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
    void resize(size_t size)
    {
        if (size > m_capacity)
        {
            size_t new_capacity = (m_capacity == 0) ? 4 : m_capacity;
            while (new_capacity < size)
            {
                new_capacity *= 2;
            }

            Data* new_data = new Data[new_capacity];
            for (size_t i = 0; i < m_size; i++)
            {
                new_data[i] = m_data[i];
            }

            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }

        m_size = size;
    }

private:
    void copy_from(const Vector& a)
    {
        if (a.m_size > 0)
        {
            m_data = new Data[a.m_size];
            m_capacity = a.m_size;
            m_size = a.m_size;
            for (size_t i = 0; i < m_size; i++)
            {
                m_data[i] = a.m_data[i];
            }
        }
    }

    Data* m_data;
    size_t m_size;
    size_t m_capacity;
};

#endif
