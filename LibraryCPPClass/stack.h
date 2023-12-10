#ifndef STACK_H
#define STACK_H

#include "list.h"  

class Stack
{
public:
    Stack();
    ~Stack();
    void push(Data data);
    Data get() const;
    void pop();
    bool empty() const;
private:
    List dataList; 
};

#endif
