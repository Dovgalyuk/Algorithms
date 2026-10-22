#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "list.h"

template <typename Data>
class Queue
{
private:
    List<Data> list_;

public:
    Queue()
    {
    }

    Queue(const Queue &a)
        : list_(a.list_)
    {
    }

    Queue &operator=(const Queue &a)
    {
        if (this != &a)
        {
            list_ = a.list_;
        }
        return *this;
    }

    ~Queue()
    {
    }

    void insert(Data data)
    {
        list_.insert_after(list_.last(), data);
    }

    Data get() const
    {
        return const_cast<List<Data>&>(list_).first()->data();
    }

    void remove()
    {
        list_.erase_first();
    }

    bool empty() const
    {
        return const_cast<List<Data>&>(list_).first() == nullptr;
    }
};

#endif