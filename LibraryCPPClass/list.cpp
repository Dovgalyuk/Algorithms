#include <cstddef>
#include "list.h"

List::List() : _head(nullptr), _tail(nullptr) {}

List::List(const List& a) : _head(nullptr), _tail(nullptr)
{
    Item* last = nullptr;
    for (Item* it = a._head; it; it = it->_next)
    {
        last = insert_after(last, it->_data);
    }
}

List& List::operator=(const List& a)
{
    if (this != &a)
    {
        while (_head)
        {
            erase_first();
        }
        Item* last = nullptr;
        for (Item* it = a._head; it; it = it->_next)
        {
            last = insert_after(last, it->_data);
        }
    }
    return*this;
}

List::~List()
{
    while (_head)
    {
        erase_first();
    }
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
        if (_head)
        {
            _head->_prev = new_item;
            new_item->_next = _head;
        }
        _head = new_item;
        if (!_tail) _tail = new_item;
    }
    else
    {
        new_item->_next = item->_next;
        new_item->_prev = item;

        if (item->_next) item->_next->_prev = new_item;

        item->_next = new_item;
        if (item == _tail) _tail = new_item;
    }

    return new_item;
}

List::Item* List::erase_first()
{
    return erase_next(nullptr);
}

List::Item* List::erase_next(Item* item)
{
    Item* to_delete;
    if (!item)
    {
        if (!_head) return nullptr;

        to_delete = _head;
        _head = _head->_next;
        if (_head) _head->_prev = nullptr;
        if (to_delete == _tail) _tail = nullptr;
    }
    else
    {
        to_delete = item->_next;
        if (!to_delete) return nullptr;

        item->_next = to_delete->_next;
        if (to_delete->_next) to_delete->_next->_prev = item;
        if (to_delete == _tail) _tail = item;
    }

    delete to_delete;

    return item ? item->_next : _head;
}
