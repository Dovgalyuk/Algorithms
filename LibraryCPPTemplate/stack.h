#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include "vector.h"

template <typename Data> class Stack
{
public:
    // Creates empty stack
    Stack()
    {
    }
    // copy constructor
    Stack(const Stack &a) : elements(a.elements)
    {
    }
    // assignment operator
    Stack &operator=(const Stack &a)
    {
        if (this != &a)
        {
            elements = a.elements;
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
        elements.resize(elements.size() + 1);
        elements.set(elements.size() - 1, data);
    }
    // Retrieves the last element from the stack
    Data get() const
    {
        return elements.get(elements.size() - 1);
    }
    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        elements.resize(elements.size() - 1);
    }
    // Returns true if the stack is empty
    bool empty() const
    {
        return elements.size() == 0;
    }
private:
    Vector<Data> elements;
};
#endif
