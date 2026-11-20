#include "queue.h"

void Queue::insert(Data data) {
    list_.insert_after(list_.last(), data);
}

Data Queue::get() const {
    const List::Item* front = list_.first();
    if (front == nullptr) {
        return Data();
    }
    return front->data();
}

void Queue::remove() {
    list_.erase_first();
}

bool Queue::empty() const {
    return list_.first() == nullptr;
}