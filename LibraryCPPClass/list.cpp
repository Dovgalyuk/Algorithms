#include <cstddef>
#include "list.h"

List::List() : m_head(nullptr), m_tail(nullptr) {}

List::List(const List &a) : m_head(nullptr), m_tail(nullptr)
{
    for (Item *p = a.m_head; p; p = p->m_next) {
        insert(p->m_data);
    }
}

List &List::operator=(const List &a)
{
    if (this == &a) {
        return *this;
    }

    while (m_head) {
        erase_first();
    }

    for (Item *p = a.m_head; p; p = p->m_next) {
        insert(p->m_data);
    }

    return *this;
}

List::~List()
{
    while (m_head) {
        erase_first();
    }

    m_tail = nullptr;
}

List::Item *List::first()
{
    return m_head;
}

const List::Item *List::first() const
{
    return m_head;
}

List::Item *List::insert(Data data)
{
    Item *it = new Item;
    it->m_data = data;
    it->m_next = m_head;
    it->m_prev = nullptr;

    if (m_head)
        m_head->m_prev = it;
    else
        m_tail = it;  

    m_head = it;
    return it;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if (item == nullptr)
        return insert(data);

    Item *it = new Item;
    it->m_data = data;
    it->m_prev = item;
    it->m_next = item->m_next;

    if (item->m_next)
        item->m_next->m_prev = it;
    else
        m_tail = it;

    item->m_next = it;
    return it;
}

List::Item *List::erase_first()
{
    if (!m_head) return nullptr;

    Item *next = m_head->m_next;

    delete m_head;
    m_head = next;

    if (next)
        next->m_prev = nullptr;
    else
        m_tail = nullptr;

    return next;
}

List::Item *List::erase_next(Item *item)
{
    if (item == nullptr)
        return erase_first();

    Item *target = item->m_next;

    if (!target) 
        return nullptr;

    Item *next = target->m_next;

    item->m_next = next;

    if (next)
        next->m_prev = item;
    else
        m_tail = item; 

    delete target;
    return next;
}
