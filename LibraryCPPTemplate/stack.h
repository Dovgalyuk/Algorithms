#ifndef STACK_H
#define STACK_H
#include "list.h"

template <typename Data> class Stack
{
public:
    // Creates empty stack
    Stack()
    {
        list = new List<Data>;
    }

    // Deletes the stack
    ~Stack()
    {
        delete list;
    }

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data)
    {
        list->insert(data);
    }

    // Retrives the last element from the stack
    Data get()
    {
       return list->first()->data();
    }

    // Removes the last element from the stack
    // Should be O(1)
    void pop()
    {
        if (!empty()){
            list->erase(list->first());
        }
    }

    // Returns true if the stack is empty
    bool empty()
    {
        return !list->first();
    }

private:
    // private data should be here
    List<Data> *list;
};

#endif
