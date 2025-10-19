#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include "vector.h"
#include <string>

// Change it to desired type
typedef std::string Data;

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

    // Removes the last element from the stack
    // Should be O(1)
    void pop();

    // Returns true if the stack is empty
    bool empty() const;

private:
    // private data should be here
    Vector box;
   
    
};

#endif
