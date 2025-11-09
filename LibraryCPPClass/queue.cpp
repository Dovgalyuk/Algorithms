#include "queue.h"
#include <stdexcept>
#include "list.h"

Queue::Queue(): _list(new List()) {};

Queue::Queue(const Queue &a): _list(new List(*a._list)) {}

Queue &Queue::operator=(const Queue &a)
{
    if (this != &a) {
        _list = a._list;
    }
    return *this;
}

Queue::~Queue() {
    delete _list;
};

void Queue::insert(Data data)
{
    _list -> insert_end(data);
}

Data Queue::get() const
{
    if (empty())
    {
        throw std::runtime_error("Queue is empty");
    }
    return _list -> first()->data();
}

void Queue::remove()
{
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }
    _list -> erase_first();
}

bool Queue::empty() const
{
    return _list -> first() == nullptr;
}
