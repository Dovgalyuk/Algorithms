#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include "vector.h"

template <typename Data> class Stack
{
public:
    Stack() {}

    Stack(const Stack& other)
        : m_storage(other.m_storage)
    {
    }

    Stack& operator=(const Stack& other)
    {
        if (this != &other)
        {
            m_storage = other.m_storage;
        }
        return *this;
    }

    ~Stack() {}

    void push(const Data& value)
    {
        const size_t index = m_storage.size();
        m_storage.resize(index + 1);
        m_storage.set(index, value);
    }

    Data get() const
    {
        if (empty())
        {
            throw std::out_of_range("Get empty");
        }
        return m_storage.get(m_storage.size() - 1);
    }

    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Pop empty");
        }
        m_storage.resize(m_storage.size() - 1);
    }

    bool empty() const
    {
        return m_storage.size() == 0;
    }

private:
    Vector<Data> m_storage;
};

#endif