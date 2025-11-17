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

List::Item *List::last() {
    return _tail;
}

const List::Item *List::last() const {
    return _tail;
}

List::Item *List::insert(Data data)
{
    Item *new_item = new Item(data);
    new_item->_next = _head;
    _head = new_item;
    
    if (!_tail) {
        _tail = new_item;
    }
    
    return new_item;
}

List::Item *List::insert_end(Data data) {
    Item *new_item = new Item(data);
    
    if (_tail) {
        _tail->_next = new_item;
        _tail = new_item;
    } else {
        _head = _tail = new_item;
    }
    
    return new_item;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if (!item) {
        return insert(data);
    }
    
    Item *new_item = new Item(data);
    new_item->_next = item->_next;
    item->_next = new_item;
    
    if (item == _tail) {
        _tail = new_item;
    }
    
    return new_item;
}

List::Item *List::erase(Item *item) {
    if (!item) return nullptr;
    
    if (item == _head) {
        return erase_first();
    }
    
    Item* prev = _head;
    while (prev && prev->_next != item) {
        prev = prev->_next;
    }
    
    if (!prev) return nullptr;
    
    prev->_next = item->_next;
    
    if (item == _tail) {
        _tail = prev;
    }
    
    Item* result = item->_next;
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
        if (!_head) return nullptr;
        
        Item* to_delete = _head;
        _head = _head->_next;
        
        if (!_head) {
            _tail = nullptr;
        }
        
        Item* result = _head;
        delete to_delete;
        return result;
    } else {
        if (!item->_next) return nullptr;
        
        Item* to_delete = item->_next;
        item->_next = to_delete->_next;
        
        if (to_delete == _tail) {
            _tail = item;
        }
        
        Item* result = item->_next;
        delete to_delete;
        return result;
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
        current = current->_next;
        src = src->_next;
    }
    
    _tail = current;
}

void List::clear() {
    while (_head) {
        erase_first();
    }
}
