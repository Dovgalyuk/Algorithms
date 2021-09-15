#ifndef STACK_H
#define STACK_H

#include "list.h"

template <typename Data> class Stack: private List<Data>
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
            lastItem = this->insert(data);
        } else {
            lastItem = this->insert_after(lastItem, data);
        }
    }

    // Retrives the last element from the stack
    Data get() const
    {
        return lastItem->data();
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        auto* prev = lastItem->prev();
        this->erase(lastItem);
        lastItem = prev;
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return !(this->firstItem);
    }

protected:
    typename List<Data>::Item* lastItem = nullptr;
};

#endif
