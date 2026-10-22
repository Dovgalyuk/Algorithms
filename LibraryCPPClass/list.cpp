#include "list.h"

List::List() {
    m_barrier = new Item();
    m_barrier->m_isBarrier = true;
    m_barrier->m_next = m_barrier;
    m_barrier->m_prev = m_barrier;
}

List::List(const List &a) {
    m_barrier = new Item();
    m_barrier->m_isBarrier = true;
    m_barrier->m_next = m_barrier;
    m_barrier->m_prev = m_barrier;
    copyFrom(a);
}

List &List::operator=(const List &a) {
    if (this == &a) return *this;
    clear();
    copyFrom(a);
    return *this;
}

List::~List() {
    clear();
    delete m_barrier;
}

void List::copyFrom(const List &a) {
    Item *cur = a.m_barrier->m_next;
    while (cur != a.m_barrier) {
        insert_after(last(), cur->m_data);
        cur = cur->m_next;
    }
}

void List::clear() {
    Item *cur = m_barrier->m_next;
    while (cur != m_barrier) {
        Item *next = cur->m_next;
        delete cur;
        cur = next;
    }
    m_barrier->m_next = m_barrier;
    m_barrier->m_prev = m_barrier;
}

List::Item *List::first() {
    return (m_barrier->m_next == m_barrier) ? nullptr : m_barrier->m_next;
}

List::Item *List::last() {
    return (m_barrier->m_prev == m_barrier) ? nullptr : m_barrier->m_prev;
}

List::Item *List::insert(Data data) {
    return insert_after(m_barrier, data);
}

List::Item *List::insert_after(Item *item, Data data) {
    if (item == nullptr) item = m_barrier;

    Item *newItem = new Item();
    newItem->m_data = data;
    newItem->m_next = item->m_next;
    newItem->m_prev = item;
    item->m_next->m_prev = newItem;
    item->m_next = newItem;
    return newItem;
}

List::Item *List::erase_first() {
    return erase_next(m_barrier);
}

List::Item *List::erase_next(Item *item) {
    if (item == nullptr) item = m_barrier;

    Item *toDelete = item->m_next;
    if (toDelete == m_barrier) return nullptr;

    Item *next = toDelete->m_next;
    item->m_next = next;
    next->m_prev = item;
    delete toDelete;
    return next;
}