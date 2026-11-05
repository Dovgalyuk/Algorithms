#include "queue.h"

Queue::Queue() {}

Queue::Queue(const Queue& a) : list(a.list) {}

Queue& Queue::operator=(const Queue& a) {
    if (this != &a) list = a.list;
    return *this;
}

Queue::~Queue() {}

void Queue::insert(Data data) {
    list.insert_after(list.last(), data);
}

Data Queue::get() const {
    return list.first()->data();
}

void Queue::remove() {
    list.erase_first();
}

bool Queue::empty() const {
    return list.first() == nullptr;
}
