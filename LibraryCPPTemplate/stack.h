#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

template <typename Data> 
class Stack
{
public:
    // Creates empty stack
    Stack() 
        : m_data(nullptr), m_size(0), m_capacity(0)
    { }

    // copy constructor
    Stack(const Stack &a) 
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
    Stack &operator=(const Stack &a)
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

    // Deletes the stack
    ~Stack()
    {
        delete[] m_data;
    }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data value)
    {
        if (m_size == m_capacity) {
            size_t newm_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            Data *newm_data = new Data[newm_capacity];

            for (size_t i = 0; i < m_size; ++i) {
                newm_data[i] = m_data[i];
            }

            delete[] m_data;
            m_data = newm_data;
            m_capacity = newm_capacity;
        }

        m_data[m_size++] = value;
    }

    // Retrieves the last element from the stack
    Data get() const
    {
        if (m_size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return m_data[m_size - 1];
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        if (m_size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        --m_size;
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return m_size == 0;
    }

private:
    // private data should be here
    Data *m_data;
    size_t m_size;
    size_t m_capacity;
};

#endif
