#include <cstddef>
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
    if (_size == 0) {
        _firstItem = nullptr;
        _lastItem = nullptr;
    } else {
        _firstItem = new Item(nullptr, nullptr, a._firstItem->data());

        if (a._firstItem->next() == nullptr) {
            _lastItem = _firstItem;
        } else {
            Item *nextItem = a._firstItem->next();
            Item *nextNewItem = new Item(_firstItem, nullptr, a._firstItem->next()->data());
            for (; nextItem->next() != nullptr; nextItem = nextItem->next()) {
                nextNewItem = new Item(nextNewItem, nullptr, nextItem->next()->data());
                nextNewItem->prev()->_setNext(nextNewItem);
            }
            _lastItem = nextNewItem;
        }
    }
}

List &List::operator=(const List &a) {
    return *this;
}

List::~List() {
    _size = 0;
    for (Item *data = _firstItem->next(); data->next() != nullptr; data = data->next()) {
        delete data->prev();
    }
    delete _firstItem;
    delete _lastItem;
}

List::Item *List::first() {
    return _firstItem;
}

List::Item *List::insert(Data data) {
    _firstItem = new Item(nullptr, _firstItem, data);
    _size++;
    return _firstItem;
}

List::Item *List::insert_after(Item *item, Data data) {
    Item *newItem = new Item(item, item->next(), data);;
    if (item->next() == nullptr) {
        item->_setNext(newItem);
        _lastItem = newItem;
    } else {
        Item *leftItem = item;
        Item *rightItem = item->next();
        leftItem->_setNext(newItem);
        rightItem->_setPrev(newItem);
    }
    _size++;

    return newItem;
}

List::Item *List::erase_first() {
    // Create new first item
    _firstItem = _firstItem->next();
    _firstItem->_setPrev(nullptr);

    return _firstItem;
}

List::Item *List::erase_next(Item *item) {
    Item *leftItem = item->prev();
    Item *rightItem = item->next();

    // If it Item is first
    if (leftItem != nullptr) {
        leftItem->_setNext(rightItem);
    }

    rightItem->_setPrev(leftItem);
    return rightItem;
}
