#include "list.h"

List::List() {
    dummy = new Item;
    dummy->data = 0;
    dummy->next = dummy;
    dummy->prev = dummy;
}

List::List(const List& other) {
    dummy = new Item;
    dummy->data = 0;
    dummy->next = dummy;
    dummy->prev = dummy;

    Item* current = other.dummy->next;
    while (current != other.dummy) {
        insert(current->data);
        current = current->next;
    }
}

List& List::operator=(const List& other) {
    if (this != &other) {
        List clone(other);
        Item* temp = this->dummy;
        this->dummy = clone.dummy;
        clone.dummy = temp;
    }
    return *this;
}

List::~List() {
    Item* current = dummy->next;
    while (current != dummy) {
        Item* nextItem = current->next;
        delete current;
        current = nextItem;
    }
    delete dummy;
}

List::Item* List::first() const {
    if (dummy->next == dummy) return nullptr;
    return dummy->next;
}

bool List::empty() const {
    return dummy->next == dummy;
}

List::Item* List::insert(Data data) {
    Item* newItem = new Item;
    newItem->data = data;

    newItem->prev = dummy->prev;
    newItem->next = dummy;

    dummy->prev->next = newItem;
    dummy->prev = newItem;

    return newItem;
}

List::Item* List::erase(Item* item) {
    if (item == nullptr || item == dummy) return nullptr;

    Item* nextItem = item->next;
    item->prev->next = item->next;
    item->next->prev = item->prev;

    delete item;

    if (nextItem == dummy) return nullptr;
    return nextItem;
}
