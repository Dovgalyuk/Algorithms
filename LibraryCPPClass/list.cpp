#include <cstddef>
#include "list.h"

List::Item::Item(Data data) : _prev(nullptr), _next(nullptr), _data(data) {
}

List::Item *List::Item::prev(){
    return _prev;
}
List::Item *List::Item::next() {
    return _next;
}
Data List::Item::data() const {
    return _data;
}

// List
// List constructor
List::List() : _list(nullptr) {
}

// Copy constructor
List::List(const List &a) : _list(nullptr) {
    if (a._list == nullptr) return;

    _list = new Item(a._list->data());
    Item *newItem = _list;
    _listLast = newItem;

    for (Item *curr = a._list->next(); curr != nullptr; curr = curr->next()) {
        newItem->_next = new Item(curr->data());
        newItem->_next->_prev = newItem;
        newItem = newItem->_next;
    }
}

List &List::operator=(const List &a) {
    if (this == &a) return *this;
    while (_list != nullptr) {
        erase_first();
    }
    if (!a._list) return *this;

    _list = new Item(a._list->data());
    Item *newItem = _list;
    _listLast = newItem;

    for (Item *curr = a._list->next(); curr != nullptr; curr = curr->next()) {
        newItem->_next = new Item(curr->data());
        newItem->_next->_prev = newItem;
        newItem = newItem->_next;
    }

    return *this;
}

List::~List() {
    while (_list != nullptr) {
        erase_first();
    }
}

// Retrieves the first item from the list
List::Item *List::first() {
    return _list;
}

// Retrieves the last item from the list
List::Item *List::last() {
    return _listLast;
}

// Inserts new list item into the beginning
List::Item *List::insert(Data data) {
    Item *newItem = new Item(data);
    if (_list != nullptr) {
        _list->_prev = newItem;
        newItem->_next = _list;
    } else {
        _listLast = newItem;
    }
    _list = newItem;

    return newItem;
}

// Inserts new list item after the specified item
List::Item *List::insert_after(Item *item, Data data) {
    if (item == nullptr) return nullptr;

    Item *newItem = new Item(data);
    newItem->_next = item->next();
    newItem->_prev = item;

    newItem->prev()->_next = newItem;
    if (newItem->next() == nullptr) {
        _listLast = newItem;
    } else {
        newItem->next()->_prev = newItem;
    }

    return newItem;
}

// Deletes the first list item.
// Returns pointer to the item next to the deleted one.
List::Item *List::erase_first() {
    if (_list == nullptr) return nullptr;

    Item *nextItem = _list->next();
    if (nextItem != nullptr) {
        nextItem->_prev = nullptr;
    } else {
        _listLast = nullptr;
        _list = nullptr;
    }

    delete _list;
    _list = nextItem;
    return _list;
}

// Deletes the list item following the specified one.
// Returns pointer to the item next to the deleted one.
// Should be O(1)
List::Item *List::erase_next(Item *item) {
    if (item == nullptr || item->next() == nullptr) return nullptr;

    Item *itemDelete = item->next();
    if (itemDelete->next() == nullptr) {
        _listLast = item;
    }
    item->_next = itemDelete->next();

    delete itemDelete;
    return item->next();
}