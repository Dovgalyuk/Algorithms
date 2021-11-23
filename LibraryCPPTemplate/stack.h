#ifndef STACK_H
#define STACK_H

#include "vector.h"

template <typename Data> class Stack
{
public:
// Creates empty stack
    Stack() : _size(0), _vector(new Vector<Data>)
    {
    }

// Deletes the stack
    ~Stack()
    {
        delete _vector;
    }

// Pushes data on top of the stack
// Should be O(1) on average
    void push(Data data)
    {
        _vector->set(_size, data);
        ++_size;
    }

// Retrives the last element from the stack
    Data get() const
    {
        return _vector->get(_size - 1);
    }

// Removes the last element from the stack
// Should be O(1)
    void pop()
    {
        --_size;
    }

// Returns true if the stack is empty
    bool empty() const
    {
        return _size == 0;
    }

private:
    Vector<Data>* _vector;
    size_t _size;
// private data should be here
};

#endif