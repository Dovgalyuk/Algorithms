#include "list.h"

List::List() {
    dummy = new Item;
    dummy->itemData = 0;
    dummy->nextItem = dummy;
    dummy->prevItem = dummy;
    dummy->isDummy = true;
}

List::List(const List& a) {
    dummy = new Item;
    dummy->itemData = 0;
    dummy->nextItem = dummy;
    dummy->prevItem = dummy;
    dummy->isDummy = true;
    Item* current = a.dummy->nextItem;
    while (current != a.dummy) {
        insert_after(last(), current->itemData);
        current = current->nextItem;
    }
}

List& List::operator=(const List& a) {
    if (this != &a) {
        List temp(a);
        Item* tempDummy = dummy;
        dummy = temp.dummy;
        temp.dummy = tempDummy;
    }
    return *this;
}

List::~List() {
    Item* current = dummy->nextItem;
    while (current != dummy) {
        Item* nextItem = current->nextItem;
        delete current;
        current = nextItem;
    }
    delete dummy;
}

List::Item* List::first() const {
    if (dummy->nextItem == dummy) return nullptr;
    return dummy->nextItem;
}

List::Item* List::last() const {
    if (dummy->prevItem == dummy) return nullptr;
    return dummy->prevItem;
}

List::Item* List::insert(Data data) {
    Item* newItem = new Item;
    newItem->itemData = data;
    newItem->isDummy = false;
    newItem->nextItem = dummy->nextItem;
    newItem->prevItem = dummy;
    dummy->nextItem->prevItem = newItem;
    dummy->nextItem = newItem;
    return newItem;
}

List::Item* List::insert_after(Item* item, Data data) {
    if (item == nullptr) return insert(data);
    Item* newItem = new Item;
    newItem->itemData = data;
    newItem->isDummy = false;
    newItem->nextItem = item->nextItem;
    newItem->prevItem = item;
    item->nextItem->prevItem = newItem;
    item->nextItem = newItem;
    return newItem;
}

List::Item* List::erase_first() {
    if (dummy->nextItem == dummy) return nullptr;
    Item* toDelete = dummy->nextItem;
    Item* nextItem = toDelete->nextItem;
    dummy->nextItem = nextItem;
    nextItem->prevItem = dummy;
    delete toDelete;
    if (nextItem == dummy) return nullptr;
    return nextItem;
}

List::Item* List::erase_next(Item* item) {
    if (item == nullptr) return erase_first();
    Item* toDelete = item->nextItem;
    if (toDelete == dummy) return nullptr;
    Item* nextItem = toDelete->nextItem;
    item->nextItem = nextItem;
    nextItem->prevItem = item;
    delete toDelete;
    if (nextItem == dummy) return nullptr;
    return nextItem;
}
