#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include <stdexcept>

#include "vector.h"

template <typename Data>
class Stack
{
public:
    // Creates an empty stack
    Stack() = default;

    // Copies the internal vector
    Stack(const Stack &a) = default;

    // Assigns the internal vector
    Stack &operator=(const Stack &a) = default;

    // The internal vector frees its memory
    ~Stack() = default;

    // Adds an element to the top
    void push(Data data)
    {
        size_t index = values.size();

        values.resize(index + 1);
        values.set(index, data);
    }

    // Returns the top element without removing it
    Data get() const
    {
        if (empty())
        {
            throw std::out_of_range("Stack is empty");
        }

        return values.get(values.size() - 1);
    }

    // Removes the top element
    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Stack is empty");
        }

        values.resize(values.size() - 1);
    }

    // Checks whether the stack is empty
    bool empty() const
    {
        return values.size() == 0;
    }

private:
    Vector<Data> values;
};

#endif