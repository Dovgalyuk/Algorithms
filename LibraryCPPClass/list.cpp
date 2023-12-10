#include <cstddef>
#include "list.h"

List::List() : head(nullptr), tail(nullptr) {}

List::List(const List &a) : head(nullptr), tail(nullptr) {
    Item *temp = a.first();
    while (temp != nullptr) {
        this->insert(temp->data());
        temp = temp->next();
    }
}

List &List::operator=(const List &a) {
    if (this != &a) {
        Item *temp = head;
        while (temp != nullptr) {
            Item *next = temp->next();
            delete temp;
            temp = next;
        }
        head = nullptr;
        tail = nullptr;
        temp = a.first();
        while (temp != nullptr) {
            this->insert(temp->data());
            temp = temp->next();
        }
    }
    return *this;
}

List::~List() {
    Item *temp = head;
    while (temp != nullptr) {
        Item *next = temp->next();
        delete temp;
        temp = next;
    }
}

List::Item *List::first() {
    return head;
}

List::Item *List::insert(Data data) {
    Item *newItem = new Item();
    newItem->data = data;
    newItem->next = head;
    if (head != nullptr) {
        head->prev = newItem;
    }
    head = newItem;
    if (tail == nullptr) {
        tail = newItem;
    }
    return newItem;
}

List::Item *List::insert_after(Item *item, Data data) {
    if (item == nullptr) {
        return insert(data);
    }
    Item *newItem = new Item();
    newItem->data = data;
    newItem->next = item->next();
    newItem->prev = item;
    if (item->next() != nullptr) {
        item->next()->prev = newItem;
    }
    item->next = newItem;
    if (tail == item) {
        tail = newItem;
    }
    return newItem;
}

List::Item *List::erase_first() {
    if (head == nullptr) {
        return nullptr;
    }
    Item *temp = head->next();
    delete head;
    if (temp != nullptr) {
        temp->prev = nullptr;
    }
    head = temp;
    if (tail == nullptr) {
        tail = temp;
    }
    return temp;
}

List::Item *List::erase_next(Item *item) {
    if (item == nullptr || item->next() == nullptr) {
        return nullptr;
    }
    Item *temp = item->next()->next();
    delete item->next();
    item->next = temp;
    if (temp != nullptr) {
        temp->prev = item;
    }
    if (tail == item->next()) {
        tail = item;
    }
    return temp;
}

