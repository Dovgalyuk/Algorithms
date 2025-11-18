#include "queue.h"

Queue::Queue() {
}

Queue::Queue(const Queue& a) {
    (void)a;
}

Queue& Queue::operator=(const Queue& a) {
    (void)a;
    return *this;
}

Queue::~Queue() {
}

void Queue::insert(Data data) {
    (void)data;
}

Data Queue::get() const {
    return Data(0);
}

void Queue::remove() {
}

bool Queue::empty() const {
    return true;
}
