#include <cstddef>
#include "list.h"

List::List() : head(nullptr), tail(nullptr)
{
}

List::List(const List& a) : head(nullptr), tail(nullptr)
{
    for (Item* current = a.head; current != nullptr; current = current->next_item) {
        insert_after(tail, current->value);
    }
}

List& List::operator=(const List& a)
{
    if (this != &a)
    {
        List copy(a);
        while (head != nullptr)
        {
            erase_first();
        }

        head = copy.head;
        tail = copy.tail;

        copy.head = nullptr;
        copy.tail = nullptr;
    }

    return *this;

}
    


List::~List()
{
    while (head != nullptr)
    {
        erase_first();
    }

}

List::Item *List::first()
{
    return head;
}

List::Item *List::last()
{
    return tail;
}

List::Item *List::insert(Data data)
{
    Item* item = new Item(data);
    item->next_item = head;
    head = item;
    if (tail == nullptr)
    {
        tail = item;
    }

    return item;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if (item == nullptr)
    {
        return insert(data);
    }

    Item* new_item = new Item(data);
    new_item->next_item = item->next_item;
    item->next_item = new_item;

    if (tail == item)
    {
        tail = new_item;
    }

    return new_item;

}

List::Item *List::erase_first()
{
    if (head == nullptr)
    {
        return nullptr;
    }

    Item* removed = head;
    head = head->next_item;

    if (head == nullptr)
    {
        tail = nullptr;
    }

    delete removed;
    return head;

}

List::Item *List::erase_next(Item *item)
{
    if (item == nullptr)
    {
        return erase_first();
    }

    if (item->next_item == nullptr)
    {
        return nullptr;
    }

    Item* removed = item->next_item;
    item->next_item = removed->next_item;

    if (tail == removed)
    {
        tail = item;
    }

    Item* next_item = item->next_item;
    delete removed;

    return next_item;

}
