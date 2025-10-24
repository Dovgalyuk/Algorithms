#include <cstddef>
#include "list.h"

List::List() : _head(nullptr) {}

List::List(const List& a) : _head(nullptr)
{
    copy(a);
}

List& List::operator=(const List& a)
{
    if (this != &a)
    {
        clear();
        copy(a);
    }
    return*this;
}

List::~List()
{
    clear();
}

List::Item* List::first() const
{
    return _head;
}

List::Item* List::insert(Data data)
{
    return insert_after(nullptr, data);
}

List::Item* List::insert_after(Item* item, Data data)
{
    Item* new_item = new Item(data);

    if (!item)
    {
        new_item->_next = _head;
        if (_head)
        {
            _head->_prev = new_item;
        }
        _head = new_item;
    }
    else
    {
        new_item->_next = item->_next;
        new_item->_prev = item;
        if (item->_next)
        {
            item->_next->_prev = new_item;
        }
        item->_next = new_item;
    }

    return new_item;
}

List::Item* List::erase_first()
{
    return erase_next(nullptr);
}

List::Item* List::erase_next(Item* item)
{
    Item* to_delete = item ? item->_next : _head;
    if (!to_delete)
        return nullptr;

    if (to_delete == _head)
        _head = to_delete->_next;

    if (to_delete->_next)
        to_delete->_next->_prev = to_delete->_prev;
    if (to_delete->_prev)
        to_delete->_prev->_next = to_delete->_next;

    Item* next_item = to_delete->_next;
    delete to_delete;

    return next_item;
}

void List::copy(const List& a)
{
    Item* last = nullptr;
    for (Item* it = a._head; it; it = it->_next)
    {
        last = insert_after(last, it->_data);
    }
}

void List::clear()
{
    while (_head)
    {
        erase_first();
    }
}
