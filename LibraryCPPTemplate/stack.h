#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include "list.h"

template <typename Data> 
class Stack
{
public:
    void push(Data data)
    {
        list_.insert(data);
    }


    Data pop()
    {
        Data data = list_.first()->data();
        list_.erase_first();
        return data;
    }

    Data get()
    {
        return list_.first()->data();
    }


    bool empty()
    {
        return list_.first() == nullptr;
    }

private:
    List<Data> list_;
};

#endif