#include "list.h"

List::List() : _head(nullptr)
{
}

void List::copy_list(const List& a)
{
    Item* tail = nullptr;
    for (Item* cur = a._head; cur; cur = cur->_next)
    {
        Item* node = new Item;
        node->_data = cur->_data;
        node->_next = nullptr;
        if (!_head) {
            _head = node;
        }
        else {
            tail->_next = node;
        }
        tail = node;
    }
}

List::List(const List &a): _head(nullptr)
{
    copy_list(a);
}

List &List::operator=(const List &a)
{
    if (this == &a) return *this;
    Item* cur = _head;
    while (cur) {
        Item* next = cur->_next;
        delete cur;
        cur = next;
    }
    _head = nullptr;
    copy_list(a);
    return *this;
}

List::~List()
{
    Item* cur = _head;
    while (cur) {
        Item* next = cur->_next;
        delete cur;
        cur = next;
    }
    _head = nullptr;
}

List::Item *List::first() const
{
    return _head;
}

//не использую, это для двусвязного списка
List::Item *List::last()
{
    return nullptr;
}

List::Item *List::insert(Data data)
{
    Item* node = new Item;
    node->_data = data;
    node->_next = _head;
    _head = node;
    return node;
}

//не использую, это для двусвязного списка
List::Item *List::insert_after(Item *item, Data data)
{
    return nullptr;
}

List::Item *List::erase_first()
{
    if (!_head) return nullptr;
    Item* k = _head;
    _head = _head->_next;
    delete k;
    return _head;
}

//не использую, это для двусвязного списка
List::Item *List::erase_next(Item *item)
{
    return nullptr;
}

void List::swap_first_two()
{
    if (!_head || !_head->_next) return;
    Item* a = _head;
    Item* b = a->_next;
    a->_next = b->_next;
    b->_next = a;
    _head = b;
}

void List::reverse()
{
    Item* prev = nullptr;
    Item* cur = _head;
    while (cur) {
        Item* next = cur->_next;
        cur->_next = prev;
        prev = cur;
        cur = next;
    }
    _head = prev;
}
