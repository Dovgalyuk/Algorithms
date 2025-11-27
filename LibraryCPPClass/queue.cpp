#include "queue.h"
#include "list.h"
Queue::Queue() : list(), tail(nullptr)
{
}

Queue::Queue(const Queue &a) : list(a.list), tail(nullptr)
{
    // implement or disable this function
    auto* it = list.first();

    if (it) {
        while (it->next()) it = it->next();
        tail = it;
    }


}

Queue &Queue::operator=(const Queue &a)
{
    // implement or disable this function
    if (this != &a) {
        list = a.list;
        tail = nullptr;

        auto* it = list.first();

        if (it) {
            while (it->next()) it = it->next();
            tail = it;
        }
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
    auto* f = list.first();
    auto* new_first = list.erase_first();
    if (f == tail)
    {
        tail = new_first;
    }
}

bool Queue::empty() const
{
    return list.first() == nullptr;
}
