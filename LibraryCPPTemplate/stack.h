#ifndef STACK_H
#define STACK_H

#include "vector.h"

template <typename Data> class Stack
{
public:
// Creates empty stack
    Stack() : _vector(new Vector<Data>(0))
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
        _vector->set(_vector->size(), data);
    }

// Retrives the last element from the stack
    Data get() const
    {
        return _vector->get(_vector->size() - 1);
    }

// Removes the last element from the stack
// Should be O(1)
    void pop()
    {
    _vector->resize(_vector->size()-1);
    }

// Returns true if the stack is empty
    bool empty() const
    {
        return _vector->size() == 0;
    }

private:
    Vector<Data>* _vector;
// private data should be here
};

#endif