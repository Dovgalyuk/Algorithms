#include "queue.h"
#include "list.h"
Queue::Queue() : list(), tail(nullptr)
{
}

Queue::Queue(const Queue &a) : list(a.list), tail(nullptr)
{
    // implement or disable this function
    tail = list.last();
}

Queue &Queue::operator=(const Queue &a)
{
    // implement or disable this function
    if (this != &a) {
        list = a.list;
        tail = list.last();
    }
    return *this;
}

Queue::~Queue()
{
}

void Queue::insert(Data data)
{
    if (!tail)
    {
        tail = list.insert(data);
    }
    else
    {
        tail = list.insert_after(tail, data);
    }
}

Data Queue::get() const
{
    return list.first()->data();
}

void Queue::remove()
{
    List::Item* f = list.first();
    List::Item* new_first = list.erase_first();
    if (f == tail)
    {
        tail = new_first;
    }
}

bool Queue::empty() const
{
    return list.first() == nullptr;
}
