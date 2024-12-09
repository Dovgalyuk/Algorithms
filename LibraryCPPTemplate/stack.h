#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include "list.h"

template <typename Data>
class Stack
{
public:
    // Creates empty stack
    Stack() : _list() {}

    // copy constructor
    Stack(const Stack &a) : _list(a._list) {}

    // assignment operator
    Stack &operator=(const Stack &a)
    {
        if (this != &a)
        {
            _list = a._list;
        }
        return *this;
    }

    // Deletes the stack
    ~Stack() {}

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data)
    {
        _list.insert(data);
    }

    // Retrives the last element from the stack
    Data get() const
    {
        if (_list.first() == nullptr)
        {
            throw std::runtime_error("Stack is empty");
        }
        return _list.first()->data();
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        if (_list.first() == nullptr)
        {
            throw std::runtime_error("Stack is empty");
        }
        _list.erase_first();
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return _list.first() == nullptr;
    }

private:
    List<Data> _list;
};

#endif