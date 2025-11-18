#ifndef STACK_H
#define STACK_H

#include "vector.h"
#include <stdexcept>

typedef int Data;

class Stack {
    Vector vec; 
public:
    Stack();
    Stack(const Stack& a);
    Stack& operator=(const Stack& a);
    ~Stack();

    void push(Data data);
    Data get() const;
    void pop();
    bool empty() const;
};

#endif
