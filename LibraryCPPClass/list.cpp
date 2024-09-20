#include <iostream>
#include "list.h"


List::List() {
    _size = 0;
    _firstItem = nullptr;
    _lastItem = nullptr;
}

List::List(const List &a) {
    // Copy size List
    _size = a._size;

    // Copy Items in List
    if (a._firstItem == nullptr) return;

    _firstItem = new Item(nullptr, nullptr, a._firstItem->data());
    Item *nextNewItem = _firstItem;
    for (Item *nextItem = a._firstItem->next(); nextItem != nullptr; nextItem = nextItem->next()) {
        Item *newItem = new Item(nextNewItem, nullptr, nextItem->data());
        nextNewItem->_setNext(nextNewItem);
        nextNewItem = newItem;
    }
    _lastItem = nextNewItem;
}

List &List::operator=(const List &a) {
    if (this == &a) return *this;
    while (_firstItem != nullptr) {
        erase_first();
    }

    if (a._firstItem != nullptr) return *this;
    // Copy size List
    _size = a._size;

    // Copy Items in List
    if (_size == 0) {
        _firstItem = nullptr;
        _lastItem = nullptr;
    } else {
        _firstItem = new Item(nullptr, nullptr, a._firstItem->data());

        Item *nextNewItem = _firstItem;
        for (Item *nextItem = a._firstItem; nextItem->next() != nullptr; nextItem = nextItem->next()) {
            nextNewItem = new Item(nextNewItem, nullptr, nextItem->next()->data());
            nextNewItem->prev()->_setNext(nextNewItem);
        }
        _lastItem = nextNewItem;
    }

    for (Item *item = a._firstItem; item != nullptr; item = item->next()) {
        insert(item->data());
    }

    return *this;
}

List::~List() {
    while (_firstItem != nullptr) {
        erase_first();
    }
    _size = 0;
}

List::Item *List::first() {
    return _firstItem;
}

List::Item *List::insert(Data data) {
    _firstItem = new Item(nullptr, _firstItem, data);
    if (_firstItem->next() == nullptr) {
        _lastItem = _firstItem;
    } else {
        _firstItem->next()->_setPrev(_firstItem);
    }
    _size++;
    return _firstItem;
}

List::Item *List::insert_after(Item *item, Data data) {
    Item *newItem = new Item(item, item->next(), data);
    Item *leftItem = item;
    Item *rightItem = item->next();

    if (rightItem == nullptr) {
        leftItem->_setNext(newItem);
        _lastItem = newItem;
    } else {
        leftItem->_setNext(newItem);
        rightItem->_setPrev(newItem);
    }
    _size++;

    return newItem;
}

List::Item *List::erase_first() {
    if (_firstItem->next() == nullptr) {
        _size--;
        _firstItem = nullptr;
        _lastItem = nullptr;
        return nullptr;
    }

    _firstItem = _firstItem->next();
    delete _firstItem->prev();
    _firstItem->_setPrev(nullptr);
    _size--;

    return _firstItem;
}

List::Item *List::erase_next(Item *item) {
    if (item->prev() == nullptr) {
        _size--;
        return erase_first();
    }

    Item *rightItem = nullptr;
    if (item->next() == nullptr) {
        item->prev()->_setNext(nullptr);
    } else {
        rightItem = item->next();
        item->prev()->_setNext(item->next()); // set left part
        item->next()->_setPrev(item->prev()); // set right part
    }
    delete item;
    _size--;
    return rightItem;
}
