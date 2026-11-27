#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include "list.h"

template <typename Data>
class Stack
{
public:
    Stack()
    {
    }

    Stack(const Stack &a)
    {
        stack = a.stack;
    }

    Stack &operator=(const Stack &a)
    {
        if (this != &a)
        {
            stack = a.stack;
        }
        return *this;
    }

    ~Stack()
    {
    }

    void push(Data data)
    {
        stack.insert(data);
    }

    Data get() const
    {
        if (empty())
        {
            return Data();
        }
        return stack.first()->data();
    }

    void pop()
    {
        if (!empty())
        {
            stack.erase_first();
        }
    }

    bool empty() const
    {
        return stack.first() == nullptr;
    }

private:
    List<Data> stack;
};

#endif
