#include "list.h"
#include <utility>

List::Item::Item(Data value)
    : value(value), next_item(nullptr), prev_item(nullptr)
{
}

List::Item *List::Item::next()
{
    return next_item;
}

List::Item *List::Item::next() const
{
    return next_item;
}

List::Item *List::Item::prev()
{
    return prev_item;
}

List::Item *List::Item::prev() const
{
    return prev_item;
}

Data List::Item::data() const
{
    return value;
}

List::List()
    : first_item(nullptr), last_item(nullptr)
{
}

List::List(const List &a)
    : first_item(nullptr), last_item(nullptr)
{
    for (Item *item = a.first(); item != nullptr; item = item->next())
        insert_after(last_item, item->data());
}

List &List::operator=(const List &a)
{
    if (this == &a)
        return *this;

    List temp(a);

    std::swap(first_item, temp.first_item);
    std::swap(last_item, temp.last_item);

    return *this;
}

List::~List()
{
    while (first_item != nullptr)
        erase_first();
}

List::Item *List::first()
{
    return first_item;
}

List::Item *List::first() const
{
    return first_item;
}

List::Item *List::last()
{
    return last_item;
}

List::Item *List::last() const
{
    return last_item;
}

List::Item *List::insert(Data data)
{
    Item *item = new Item(data);
    item->next_item = first_item;

    if (first_item != nullptr)
        first_item->prev_item = item;
    else
        last_item = item;

    first_item = item;
    return item;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if (item == nullptr)
        return insert(data);

    Item *new_item = new Item(data);
    new_item->prev_item = item;
    new_item->next_item = item->next_item;

    if (item->next_item != nullptr)
        item->next_item->prev_item = new_item;
    else
        last_item = new_item;

    item->next_item = new_item;
    return new_item;
}

List::Item *List::erase_first()
{
    if (first_item == nullptr)
        return nullptr;

    Item *next_item = first_item->next_item;
    delete first_item;
    first_item = next_item;

    if (first_item != nullptr)
        first_item->prev_item = nullptr;
    else
        last_item = nullptr;

    return first_item;
}

List::Item *List::erase_next(Item *item)
{
    if (item == nullptr)
        return erase_first();

    if (item->next_item == nullptr)
        return nullptr;

    Item *removed = item->next_item;
    Item *next_item = removed->next_item;
    item->next_item = next_item;

    if (next_item != nullptr)
        next_item->prev_item = item;
    else
        last_item = item;

    delete removed;
    return next_item;
}
