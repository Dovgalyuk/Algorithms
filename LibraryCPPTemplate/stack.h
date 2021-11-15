#ifndef STACK_H
#define STACK_H

#include "vector.h"
#include "cstddef"

template <typename Data> class Stack
{
public:
    // Creates empty stack
    Stack() : vector(new Vector<Data>())
    {

    }

    // Deletes the stack
    ~Stack()
    {
        delete vector;
    }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data)
    {
        vector->resize(vector->size() + 1);
        vector->set(vector->size() - 1, data);
    }

    // Retrives the last element from the stack
    Data get() const
    {
        return vector->get(vector->size() - 1);
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        vector->resize(vector->size() - 1);
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return vector->size() == 0;
    }

private:
    // private data should be here
    Vector<Data>* vector = nullptr;
};

#endif