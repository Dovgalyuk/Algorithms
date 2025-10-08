#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename Data> class Vector
{
public:
    Vector() noexcept
        : m_data(nullptr), m_size(0), m_capacity(0)
    {
    }

    explicit Vector(size_t size)
        : Vector()
    {
        resize(size);
    }

    Vector(const Vector& other)
        : Vector()
    {
        assign(other);
    }

    Vector(Vector&& other) noexcept
        : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
    {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    Vector& operator=(const Vector& other)
    {
        if (this != &other)
        {
            assign(other);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_data;
            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    ~Vector()
    {
        delete[] m_data;
    }

    Data get(size_t index) const
    {
        check_index(index);
        return m_data[index];
    }

    template <typename Value>
    void set(size_t index, Value&& value)
    {
        check_index(index);
        m_data[index] = static_cast<Data>(std::forward<Value>(value));
    }

    size_t size() const noexcept
    {
        return m_size;
    }

    void resize(size_t size)
    {
        if (size > m_capacity)
        {
            grow(size);
        }

        if (size > m_size)
        {
            for (size_t i = m_size; i < size; ++i)
            {
                m_data[i] = Data();
            }
        }

        if (size < m_size)
        {
            for (size_t i = size; i < m_size; ++i)
            {
                m_data[i] = Data();
            }
        }

        m_size = size;
    }

private:
    static Data* allocate(size_t count)
    {
        return count == 0 ? nullptr : new Data[count];
    }

    static void copy_elements(Data* dest, const Data* src, size_t count)
    {
        for (size_t i = 0; i < count; ++i)
        {
            dest[i] = src[i];
        }
    }

    void assign(const Vector& other)
    {
        if (other.m_size == 0)
        {
            delete[] m_data;
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
            return;
        }

        const size_t previous_size = m_size;

        if (other.m_size > m_capacity)
        {
            Data* replacement = allocate(other.m_size);
            try
            {
                copy_elements(replacement, other.m_data, other.m_size);
            }
            catch (...)
            {
                delete[] replacement;
                throw;
            }

            delete[] m_data;
            m_data = replacement;
            m_capacity = other.m_size;
        }
        else
        {
            copy_elements(m_data, other.m_data, other.m_size);
        }

        m_size = other.m_size;

        if (previous_size > m_size)
        {
            for (size_t i = m_size; i < previous_size && i < m_capacity; ++i)
            {
                m_data[i] = Data();
            }
        }
    }

    void grow(size_t required)
    {
        size_t new_capacity = m_capacity == 0 ? 1 : m_capacity;
        while (new_capacity < required)
        {
            new_capacity *= 2;
        }

        Data* replacement = allocate(new_capacity);
        try
        {
            if (m_size > 0)
            {
                copy_elements(replacement, m_data, m_size);
            }
        }
        catch (...)
        {
            delete[] replacement;
            throw;
        }

        delete[] m_data;
        m_data = replacement;
        m_capacity = new_capacity;
    }

    void check_index(size_t index) const
    {
        if (index >= m_size)
        {
            throw std::out_of_range("Index out of range");
        }
    }

    Data* m_data;
    size_t m_size;
    size_t m_capacity;
};

#endif