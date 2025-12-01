#ifndef STACK_TEMPLATE_H
#define STACK_TEMPLATE_H

#include "List.h"

template <typename Data>
class Stack
{
public:
    Stack() {}

    Stack(const Stack& a) : list_(a.list_) {}

    Stack& operator=(const Stack& a)
    {
        if (this != &a) {
            list_ = a.list_;
        }
        return *this;
    }

    ~Stack() {}

    void push(Data data)
    {
        list_.insert(data);
    }

    Data get() const
    {
        if (list_.first()) {
            return list_.first()->data();
        }
        return Data();
    }

    void pop()
    {
        list_.erase_first();
    }

    bool empty() const
    {
        return list_.first() == nullptr;
    }

private:
    List<Data> list_;
};

#endif // STACK_TEMPLATE_H