#include "list.h"

List::List() {
    dummy = new Item;
    dummy->data_ = 0;
    dummy->next_ = dummy;
    dummy->prev_ = dummy;
}

List::List(const List& a) {
    dummy = new Item;
    dummy->data_ = 0;
    dummy->next_ = dummy;
    dummy->prev_ = dummy;
    Item* current = a.dummy->next_;
    while (current != a.dummy) {
        insert_after(last(), current->data_);
        current = current->next_;
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
    Item* current = dummy->next_;
    while (current != dummy) {
        Item* nextItem = current->next_;
        delete current;
        current = nextItem;
    }
    delete dummy;
}

List::Item* List::first() {
    if (dummy->next_ == dummy) return nullptr;
    return dummy->next_;
}

List::Item* List::last() {
    if (dummy->prev_ == dummy) return nullptr;
    return dummy->prev_;
}

List::Item* List::insert(Data data) {
    Item* newItem = new Item;
    newItem->data_ = data;
    newItem->next_ = dummy->next_;
    newItem->prev_ = dummy;
    dummy->next_->prev_ = newItem;
    dummy->next_ = newItem;
    return newItem;
}

List::Item* List::insert_after(Item* item, Data data) {
    if (item == nullptr) return insert(data);
    Item* newItem = new Item;
    newItem->data_ = data;
    newItem->next_ = item->next_;
    newItem->prev_ = item;
    item->next_->prev_ = newItem;
    item->next_ = newItem;
    return newItem;
}

List::Item* List::erase_first() {
    if (dummy->next_ == dummy) return nullptr;
    Item* toDelete = dummy->next_;
    Item* nextItem = toDelete->next_;
    dummy->next_ = nextItem;
    nextItem->prev_ = dummy;
    delete toDelete;
    if (nextItem == dummy) return nullptr;
    return nextItem;
}

List::Item* List::erase_next(Item* item) {
    if (item == nullptr) return erase_first();
    Item* toDelete = item->next_;
    if (toDelete == dummy) return nullptr;
    Item* nextItem = toDelete->next_;
    item->next_ = nextItem;
    nextItem->prev_ = item;
    delete toDelete;
    if (nextItem == dummy) return nullptr;
    return nextItem;
}
