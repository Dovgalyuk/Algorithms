#include "list.h"
#include <cstddef>

List::List() : m_head(nullptr)
{
}

List::List(const List &a)
{
    this->m_head = nullptr;
    if (&a == this || !a.m_head)
    {
        return;
    }

    this->m_head = new Item(nullptr, nullptr, a.m_head->data());

    auto next = a.m_head->next();
    auto prev = this->m_head;
    while (next)
    {
        this->insert_after(prev, next->data());
        next = next->next();
    }
}

List &List::operator=(const List &a)
{
    this->m_head = nullptr;
    if (&a != this && a.m_head)
    {
        this->m_head = new Item(nullptr, nullptr, a.m_head->data());

        auto next = a.m_head->next();
        auto prev = this->m_head;
        while (next)
        {
            this->insert_after(prev, next->data());
            next = next->next();
        }
    }

    return *this;
}

List::~List()
{
    auto item = this->m_head;

    while (item)
    {
        auto next = item->next();
        delete item;
        item = next;
    }
}

List::Item const *List::first() const
{
    return this->m_head;
}

List::Item *List::insert(Data data)
{
    Item *item = nullptr;

    if (this->m_head)
    {
        item = new Item(nullptr, this->m_head, data);
        this->m_head->set_prev(item);
    }
    else
    {
        item = new Item(nullptr, nullptr, data);
    }

    this->m_head = item;
    return this->m_head;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if (!item || !this->m_head)
    {
        return nullptr;
    }

    auto newItem = new Item(item, item->next(), data);
    item->set_next(newItem);
    if (newItem->next())
    {
        newItem->next()->set_prev(newItem);
    }
    return newItem;
}

List::Item *List::erase_first()
{
    if (!this->m_head)
    {
        return nullptr;
    }

    auto newHead = this->m_head->next();
    delete this->m_head;
    this->m_head = newHead;
    if (this->m_head)
    {
        this->m_head->set_prev(nullptr);
    }
    return this->m_head;
}

List::Item *List::erase_next(Item *item)
{
    if (!item || !item->next() || !this->m_head)
    {
        return nullptr;
    }
    Item *newNextItem = item->next()->next();

    delete item->next();

    item->set_next(newNextItem);
    if (newNextItem)
    {
        newNextItem->set_prev(item);
    }

    return newNextItem;
}