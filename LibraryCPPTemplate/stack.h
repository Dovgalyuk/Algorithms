#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include "vector.h"

template <typename Data>
class Stack
{
public:
    // Creates empty stack
    Stack()
    {
    }

    // copy constructor
    Stack(const Stack &a) : data(a.data)
    {
        // implement or disable this function
    }

    // assignment operator
    Stack &operator=(const Stack &a)
    {
        data = a.data;
        return *this;
    }

    // Deletes the stack
    ~Stack()
    {
    }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data value)
    {
        size_t index = data.size();
        data.resize(index + 1);
        data.set(index, value);
    }

    // Retrieves the last element from the stack
    Data get() const
    {
        if (empty())
            throw std::out_of_range("Stack is empty");
        size_t index = data.size() - 1;
        return data.get(index);
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        if (empty())
            throw std::out_of_range("Stack is empty");
        size_t index = data.size() - 1;
        data.resize(index);
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        if (data.size() == 0)
            return true;
        else
        {
            return false;
        }
    }

private:
    Vector<Data> data;
};

#endif
