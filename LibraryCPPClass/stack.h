#ifndef STACK_H
#define STACK_H

#include "list.h"  // Include the header file for the List class

class Stack
{
public:
    // Creates empty stack
    Stack();

    // Deletes the stack
    ~Stack();

    // Pushes data on top of the stack
    // Should be O(1) on average
    void push(Data data);

    // Retrieves the last element from the stack
    Data get() const;

    // Removes the last element from the stack
    // Should be O(1)
    void pop();

    // Returns true if the stack is empty
    bool empty() const;

private:
    List dataList;  // Private List member
};

#endif
