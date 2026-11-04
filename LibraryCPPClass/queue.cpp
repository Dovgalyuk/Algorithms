#include "queue.h"

Queue::Queue() {}

Queue::Queue(const Queue& other) : list(other.list) {}

Queue& Queue::operator=(const Queue& other) {
    if (this != &other) {
        list = other.list;
    }
    return *this;
}

Queue::~Queue() {}

void Queue::insert(Data data) {
    list.insert(data);
}

Data Queue::get() const {
    return list.first()->data;
}

void Queue::remove() {
    list.erase(list.first());
}

bool Queue::empty() const {
    return list.empty();
}
