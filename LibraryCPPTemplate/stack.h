#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include <cstddef>
#include <stdexcept>
#include "vector.h"

template <typename Data> class Stack
{
public:
    // Creates empty stack
    Stack()
    {
    }

    // copy constructor
    Stack(const Stack &a) : items_(a.items_)
    {
    }

    // assignment operator
    Stack &operator=(const Stack &a)
    {
        items_ = a.items_;
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
        const size_t n = items_.size();
        items_.resize(n + 1);
        items_.set(n, data);
    }

    // Retrieves the last element from the stack
    Data get() const
    {
        if (empty())
            throw std::out_of_range("Stack: get from empty stack");
        return items_.get(items_.size() - 1);
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        if (empty())
            throw std::out_of_range("Stack: pop from empty stack");
        items_.resize(items_.size() - 1);
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return items_.size() == 0;
    }

private:
    Vector<Data> items_;
};

#endif
