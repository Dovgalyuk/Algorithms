#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H
#include "vector.h"
#include <string>
#include <stdexcept>


template <typename Data> class Stack
{
private:
    Vector<Data> stack;

public:
    // Creates empty stack
    Stack()
    {
    }

    // copy constructor
    Stack(const Stack &a): stack(a.stack)
    {
    }

    // assignment operator
    Stack &operator=(const Stack &a)
    {
        stack = a.stack;
        return *this;
    }

    // Deletes the stack
    ~Stack()
    {
    }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(const Data& data)
    {
        stack.resize(stack.size() + 1);
        stack.set(stack.size() - 1, data);
    }

    // Retrieves the last element from the stack
    Data get() const
    {
        if(stack.size() == 0) {
            throw std::out_of_range("ERROR: index out of range");
        }
        return stack.get(stack.size() - 1);
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        if(stack.size() == 0) {
            return;
        }
        stack.resize(stack.size() - 1);
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return stack.size() == 0;
    }

};

#endif
