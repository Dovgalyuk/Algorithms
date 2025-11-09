#include <cstddef>
#include "list.h"

List::List() = default;

List::List(const List &a)
{
    copy(a);
}

List &List::operator=(const List &a)
{
    if (this != &a) {
        clear();
        copy(a);
    }
    return *this;
}

List::~List()
{
    clear();
}

List::Item *List::first()
{
    return _head;
}

List::Item *List::insert(Data data)
{
    return insert_after(nullptr, data);
}

List::Item *List::insert_after(Item *item, Data data)
{
    Item* new_item = new Item(data);
 
    if (item)
    {
        new_item -> _next = item -> _next;
        new_item -> _prev = item;
        
        if (item -> _next)
        {
            item -> _next -> _prev = new_item;
        } else {
            _tail = new_item;
        }
        
        
        item -> _next = new_item;
        
        return new_item;
    }
    
 
    if (!_head)
    {
        _head = new_item;
        _tail = new_item;
    }
    else
    {
        new_item->_next = _head;
        _head->_prev = new_item;
        _head = new_item;
    }
    
    return new_item;
}

List::Item *List::erase(Item *item) {
    if (!item) return nullptr;
    
    Item* result = item->_next;
    
    if (item->_prev) {
        item->_prev->_next = item->_next;
    } else {
        _head = item->_next;
    }
    
    if (item->_next) {
        item->_next->_prev = item->_prev;
    } else {
        _tail = item->_prev;
    }
    
    delete item;
    return result;
}

List::Item *List::erase_first()
{
    return erase_next(nullptr);
}

List::Item *List::erase_next(Item *item)
{
    if (item == nullptr)
    {
        return erase(_head);
    } else {
        return erase(item -> _next);
    }
}

void List::copy(const List &a) {
    if (!a._head) {
        _head = _tail = nullptr;
        return;
    }

    _head = new Item(a._head->_data);
    Item *current = _head;
    Item *src = a._head->_next;

    while (src) {
        current->_next = new Item(src->_data);
        current->_next->_prev = current;
        current = current->_next;
        src = src->_next;
    }

    _tail = current;
}

void List::clear() {
    while (_head)
    {
        erase_first();
    } 
}