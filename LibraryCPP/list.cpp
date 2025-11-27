#include "list.h"

void List::copy(const List &other) {
    Item *current = other._head;
    Item *prev_copy = nullptr;

    while (current != nullptr) {
        Item *new_item = new Item(current->data());

        if (prev_copy == nullptr) {
            _head = new_item;
        } else {
            prev_copy->setNext(new_item);
            new_item->setPrev(prev_copy);
        }

        prev_copy = new_item;
        current = current->next();
    }
}

List::List() : _head(nullptr) {}

List::List(const List &a) : _head(nullptr) { copy(a); }

List &List::operator=(const List &a) {
    if (this != &a) {
        while (_head) {
            erase_first();
        }

        copy(a);
    }
    return *this;
}

List::~List() {
    while (_head != nullptr) {
        erase_first();
    }
}

List::Item *List::first() { return _head; }
const List::Item *List::first() const { return _head; }

List::Item *List::insert(Data data) {
    Item *new_item = new Item(data, _head);

    if (_head != nullptr) {
        _head->setPrev(new_item);
    }

    _head = new_item;
    return new_item;
}

List::Item *List::insert_after(Item *item, Data data) {
    if (item == nullptr) {
        return insert(data);
    }

    Item *new_item = new Item(data, item->next(), item);
    if (item->next() != nullptr) {
        item->next()->setPrev(new_item);
    }

    item->setNext(new_item);
    return new_item;
}

List::Item *List::erase_first() {
    if (_head == nullptr) {
        return nullptr;
    }

    Item *old_head = _head;
    _head = _head->next();

    if (_head != nullptr) {
        _head->setPrev(nullptr);
    }

    delete old_head;
    return _head;
}

List::Item *List::erase_next(Item *item) {
    if (item == nullptr) {
        return erase_first();
    }

    if (item->next() == nullptr) {
        return nullptr;
    }

    Item *to_delete = item->next();
    item->setNext(to_delete->next());

    if (to_delete->next() != nullptr) {
        to_delete->next()->setPrev(item);
    }

    delete to_delete;
    return item->next();
}
