#ifndef STACK_H
#define STACK_H

#include "list.h"

class Stack
{
public:
    // Creates empty stack
    Stack();

    // copy constructor
    Stack(const Stack &a);

    // assignment operator
    Stack &operator=(const Stack &a);

    // Deletes the stack
    ~Stack();

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data);

    // Retrieves the last element from the stack
    Data get() const;
    void pop();
    bool empty() const { return list_.first() == nullptr; }

private:
    List list_;
};

#endif
