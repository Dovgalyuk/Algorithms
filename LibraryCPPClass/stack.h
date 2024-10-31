#ifndef STACK_H
#define STACK_H

#include "list.h"

class Stack
{
public:
    Stack() {}
    Stack(const Stack& a) = delete;
    Stack& operator=(const Stack& a) = delete;
    ~Stack() {}

    void push(Data data) { list_.insert(data); }
    Data get() const;
    void pop();
    bool empty() const { return list_.first() == nullptr; }

private:
    List list_;
};

#endif
