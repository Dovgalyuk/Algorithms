#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>

template <typename Data> class Vector
{
public:
    Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

    Vector(const Vector& a) : m_data(nullptr), m_size(0), m_capacity(0)
    {
        m_data = copy_data(a.m_data, a.m_size);
        m_size = a.m_size;
        m_capacity = a.m_size;
    }

    Vector& operator=(const Vector& a)
    {
        if (this != &a)
        {
            Data* new_data = copy_data(a.m_data, a.m_size);

            delete[] m_data;
            m_data = new_data;
            m_size = a.m_size;
            m_capacity = a.m_size;
        }
        return *this;
    }

    ~Vector()
    {
        delete[] m_data;
    }

    Data get(size_t index) const
    {
        return m_data[index];
    }

    void set(size_t index, Data value)
    {
        m_data[index] = value;
    }

    size_t size() const
    {
        return m_size;
    }

    void resize(size_t new_size)
    {
        if (new_size <= m_capacity)
        {
            m_size = new_size;
            return;
        }

        size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity;
        while (new_capacity < new_size)
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
        m_size = new_size;
    }

private:
    Data* copy_data(const Data* src, size_t size)
    {
        if (size == 0)
        {
            return nullptr;
        }

        Data* new_data = new Data[size];
        for (size_t i = 0; i < size; ++i)
        {
            new_data[i] = src[i];
        }
        return new_data;
    }

    Data* m_data;
    size_t m_size;
    size_t m_capacity;
};

#endif
