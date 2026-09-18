#ifndef STACK_H
#define STACK_H

#include "vector.h"

class Stack
{
public:
    Stack();

    Stack(const Stack &a);

    Stack &operator=(const Stack &a);

    ~Stack();

    void push(Data data);

    Data get() const;

    void pop();

    bool empty() const;

    size_t size() const;

    Data bottom() const;

    void remove_bottom();

    Data join_to_string() const;

    void push_bottom(Data data);

private:
    Vector helper;
};

#endif
