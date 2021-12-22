#ifndef STACK_H
#define STACK_H

#include <list.h>
#include <cstddef>

template <typename Data> class Stack
{
public:
    // Creates empty stack
    Stack() : _list(new List<Data>())
    {
    }

    // Deletes the stack
    ~Stack()
    {
        delete _list;
    }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data)
    {
        _list->insert(data);
    }

    // Retrives the last element from the stack
    Data get() const
    {
        return _list->first()->data();
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        _list->erase(_list->first());
    }

    // Returns true if the stack is empty
    bool empty() const
    {
        return _list->first() == nullptr;
    }

private:
    List<Data>* _list;
    // private data should be here
};

#endif
