#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include <vector.h>

template <typename Data> class Stack
{
public:
    // Creates empty stack
    Stack()
    {
    }

    // copy constructor
    Stack(const Stack& a) : m_items(a.m_items)
    {
        // implement or disable this function
    }

    // assignment operator
    Stack &operator=(const Stack &a)
    {
        if (this != &a)
        {
            m_items = a.m_items;
        }
        return *this;
    }

    // Deletes the stack
    ~Stack()
    {
    }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data)
    {
        m_items.resize(m_items.size() + 1);
        m_items.set(m_items.size() - 1, data);
    }

    // Retrieves the last element from the stack
    Data get() const
    {
        if (m_items.size() == 0)
        {
            throw std::out_of_range("Stack is empty");
        }
        return m_items.get(m_items.size() - 1);
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        if (m_items.size() == 0)
        {
            throw std::out_of_range("Stack is empty");
        }
        m_items.resize(m_items.size() - 1);
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return m_items.size() == 0;
    }

private:
    Vector<Data> m_items;
};

#endif
