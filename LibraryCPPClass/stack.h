#ifndef STACK_H
#define STACK_H

#include "list.h"

class Stack
{
public:
    Stack();
    Stack(const Stack &a);
    Stack &operator=(const Stack &a);
    ~Stack();
    void push(Data data);
    // get and pop throw std::out_of_range when the stack is empty.
    Data get() const;
    void pop();
    bool empty() const;
private:
    List list_;
};
#endif
