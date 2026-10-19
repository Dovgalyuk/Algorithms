#include "queue.h"

Queue::Queue() {
    last = list.dummy;
}

void Queue::insert(int data) {
    last = list.insert_after(last, data);
}

int Queue::get() const {
    return list.first()->data;
}

void Queue::remove() {
    ListItem* first = list.first();
    if (first) {
        if (last == first) {
            last = list.dummy;
        }
        list.erase_after(list.dummy);
    }
}

bool Queue::empty() const {
    return list.first() == nullptr;
}
