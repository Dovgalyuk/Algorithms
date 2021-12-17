#ifndef STACK_H
#define STACK_H

#include "list.h"

template <typename Data> class Stack: List<Data>
{
public:
    // Creates empty stack
    Stack()
    {
    }
    // Deletes the stack
    ~Stack()
    {
    }
    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data)
    {
        this->insert(data);
    }

    // Retrives the last element from the stack
    Data get()
    {
        return this->first()->data();
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        this->erase(this->first());
    }

    // Returns true if the stack is empty
    bool empty()
    {
        return !(this->first());
    }

};

#endif