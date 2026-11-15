#ifndef QUEUE_TEMPLATE_H
#define QUEUE_TEMPLATE_H

#include "vector.h"
#include <cstddef>
#include <stdexcept>

template <typename Data> class Queue
{
public:
    Queue() : first(0), count(0) { buffer.resize(4); }

    Queue(const Queue &a)
        : buffer(a.buffer), first(a.first), count(a.count) {}

    Queue &operator=(const Queue &a)
    {
        if (this != &a) {
            buffer = a.buffer;
            first = a.first;
            count = a.count;
        }
        return *this;
    }

    ~Queue() {}

    void insert(Data data)
    {
        if (count == buffer.size()) {
            Vector<Data> bigger;
            bigger.resize(buffer.size() * 2);
            for (size_t i = 0; i < count; i++) {
                bigger.set(i, buffer.get((first + i) % buffer.size()));
            }
            buffer.swap(bigger);
            first = 0;
        }

        size_t last = (first + count) % buffer.size();
        buffer.set(last, data);
        count++;
    }

    Data get() const
    {
        if (empty())
            throw std::out_of_range("Queue is empty");
        return buffer.get(first);
    }

    void remove()
    {
        if (empty())
            throw std::out_of_range("Queue is empty");

        first = (first + 1) % buffer.size();
        count--;
        if (count == 0)
            first = 0;
    }

    bool empty() const { return count == 0; }

private:
    Vector<Data> buffer;
    size_t first;
    size_t count;
};

#endif
