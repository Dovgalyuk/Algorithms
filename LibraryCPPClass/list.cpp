#include "list.h"

List::List() : m_first(nullptr), m_last(nullptr) {}

List::List(const List& a)
{
    m_first = m_last = nullptr;
    copy_from(a);
}

List& List::operator=(const List& a)
{
    if (this != &a)
    {
        clear();
        copy_from(a);
    }
    return *this;
}

List::~List()
{
    clear();
}

void List::clear()
{
    Item* cur = m_first;
    while (cur)
    {
        Item* next = cur->m_next;
        delete cur;
        cur = next;
    }
    m_first = m_last = nullptr;
}

void List::copy_from(const List& a)
{
    for (Item* p = a.m_first; p; p = p->m_next)
        insert(p->m_data);
}

List::Item* List::first() const
{
    return m_first;
}

List::Item* List::last() const
{
    return m_last;
}

bool List::empty() const
{
    return m_first == nullptr;
}

List::Item* List::insert(Data data)
{
    Item* item = new Item(data);
    item->m_next = m_first;
    item->m_prev = nullptr;

    if (m_first)
        m_first->m_prev = item;
    m_first = item;

    if (!m_last)
        m_last = item;

    return item;
}

List::Item* List::insert_after(Item* pos, Data data)
{
    if (pos == nullptr)
        return insert(data);

    Item* item = new Item(data);
    item->m_next = pos->m_next;
    item->m_prev = pos;

    if (pos->m_next)
        pos->m_next->m_prev = item;
    pos->m_next = item;

    if (m_last == pos)
        m_last = item;

    return item;
}

List::Item* List::erase_first()
{
    if (!m_first)
        return nullptr;

    Item* next = m_first->m_next;
    delete m_first;
    m_first = next;

    if (m_first)
        m_first->m_prev = nullptr;
    else
        m_last = nullptr;

    return m_first;
}

List::Item* List::erase_next(Item* item)
{
    if (!item)
        return erase_first();

    Item* victim = item->m_next;
    if (!victim)
        return nullptr;

    Item* next = victim->m_next;
    item->m_next = next;
    if (next)
        next->m_prev = item;
    else
        m_last = item;

    delete victim;
    return next;
}

void List::erase(Item* item)
{
    if (!item) return;

    if (item->m_prev)
        item->m_prev->m_next = item->m_next;
    else
        m_first = item->m_next;

    if (item->m_next)
        item->m_next->m_prev = item->m_prev;
    else
        m_last = item->m_prev;

    delete item;
}