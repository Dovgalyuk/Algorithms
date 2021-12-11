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
        if (!this->first()) {
            this->firstItem = this->insert(data);
        } else {
            this->firstItem = this->insert_after(this->firstItem, data);
        }
    }

    // Retrives the last element from the stack
    Data get() const
    {
        return this->firstItem->data();
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        auto* prev = this->firstItem->prev();
        this->erase(this->firstItem);
        this->firstItem = prev;
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return !(this->firstItem);
    }

};

#endif