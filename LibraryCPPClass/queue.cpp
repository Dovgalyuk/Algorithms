#include "queue.h"

Queue::Queue() {}

Queue::Queue(const Queue &a) : m_list(a.m_list) {}

Queue &Queue::operator=(const Queue &a) {
    if (this != &a) {
        m_list = a.m_list;
    }
    return *this;
}

Queue::~Queue() {}

void Queue::insert(Data data) {
    m_list.insert_after(m_list.last(), data);
}

Data Queue::get() const {
    List::Item *item = const_cast<List &>(m_list).first();
    return item ? item->data() : Data();
}

void Queue::remove() {
    m_list.erase_first();
}

bool Queue::empty() const {
    return const_cast<List &>(m_list).first() == nullptr;
}