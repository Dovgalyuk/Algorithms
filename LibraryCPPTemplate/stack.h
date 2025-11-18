#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include <cstddef>
#include <stdexcept>

#include "vector.h"

template <typename Data> 
class Stack
{
public:
    // Creates empty stack
    Stack() 
        : m_data()
    { }

    // copy constructor
    Stack(const Stack &a) 
        : m_data(a.m_data)
    { }

    // assignment operator
    Stack &operator=(const Stack &a)
    {
        if (this != &a)
            m_data = a.m_data;
        return *this;
    }

    // Deletes the stack
    ~Stack()
    { }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data value)
    {
        size_t size = m_data.size();
        m_data.resize(size + 1);

        m_data.set(size, value);
    }

    // Retrieves the last element from the stack
    Data get() const
    {
        return m_data.get(m_data.size() - 1);
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        size_t size = m_data.size();
        if (size == 0) {
            throw std::out_of_range("Stack is empty");
        }
        m_data.resize(size - 1);
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return m_data.size() == 0;
    }

private:
    // private data should be here
    Vector<Data> m_data;
};

#endif
