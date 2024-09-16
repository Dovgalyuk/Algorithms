#include <cstddef>
#include "list.h"


List::List() {
    _size = 0;
    _firstItem = nullptr;
    _lastItem = nullptr;
}

List::List(const List &a) {
    // Copy size list
    _size = a._size;

    // Copy Item in list
    Item *itemIt = _firstItem;
    for (size_t i = 0; i < _size; i++){
        Item *copyItem = itemIt->_iterator();
        if (copyItem == nullptr){
            break;
        } else {
            if (i == 0) {
                _firstItem = new Item(nullptr, nullptr, copyItem->data());
                _lastItem = _firstItem;
            }
            Item *nextItem = new Item(_lastItem, nullptr, copyItem->data());
            _lastItem->_setNext(nextItem);
            _lastItem = nextItem;
        }

        // Copy Item
    }
}

List &List::operator=(const List &a) {
    return *this;
}

List::~List() {
    _size = 0;
    _firstItem = nullptr;
    _lastItem = nullptr;
}

List::Item *List::first() {
    return _firstItem;
}

List::Item *List::insert(Data data) {
    Item *newItem;
    if (_firstItem == nullptr) {
        newItem = new Item(nullptr, nullptr, data);
        _lastItem = newItem;
    } else {
        newItem = new Item(nullptr, _firstItem, data);
        _firstItem->_setPrev(newItem);
    }
    _firstItem = newItem;
    _size++;

    return newItem;
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
