#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include <exception>
#include "vector.h"

template <typename Data>
class Queue
{
public:
    Queue() : first(0), length(0)
    {
    }

    Queue(const Queue &a) : queue(a.queue), first(a.first), length(a.length)
    {
    }

    Queue &operator=(const Queue &a)
    {
        if (this != &a)
        {
            queue = a.queue;
            first = a.first;
            length = a.length;
        }
        return *this;
    }

    ~Queue()
    {
    }

    void insert(Data data)
    {
        if (length == queue.size())
        {
            size_t old_size = queue.size();
            size_t new_size = old_size == 0 ? 1 : old_size * 2;

            queue.resize(new_size);
            if (first > 0)
            {
                for (size_t i = 0; i < first; i++)
                {
                    queue.set(old_size + i, queue.get(i));
                    queue.set(i, Data());
                }
            }
        }
        queue.set((first + length) % queue.size(), data);
        length++;
    }

    Data get() const
    {
        if (empty())
        {
            throw std::out_of_range("queue subscript out of range");
        }
        return queue.get(first);
    }

    void remove()
    {
        if (empty())
        {
            throw std::out_of_range("queue subscript out of range");
        }
        queue.set(first, Data());
        first = (first + 1) % queue.size();
        length--;
    }

    bool empty() const
    {
        return length == 0;
    }

private:
    Vector<Data> queue;
    size_t first;
    size_t length;
};

#endif
