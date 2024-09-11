#include <cstddef>
#include "list.h"

List::Item::Item(Data data) : data_(data), next_(nullptr), prev_(nullptr) 
{
}

List::Item *List::Item::next() {
    return next_;
}

List::Item *List::Item::prev() {
    return prev_;
}

Data List::Item::data() const {
    return data_;
}

//List constructor
List::List() : head_(nullptr), tail_(nullptr) 
{
}

// Copy constructor
List::List(const List &a) : head_(nullptr), tail_(nullptr) {
    for (Item *curr = a.head_; curr != nullptr; curr = curr->next()) {
        insert(curr->data());
    }
}

List &List::operator=(const List &a)
{
    if (this == &a) return *this;
    while (head_) {
        erase_first();
    }                        
    for (Item *curr = a.head_; curr != nullptr; curr = curr->next()) {
        insert(curr->data());
    }
    return *this;
}

List::~List()
{
    while (head_) {
        erase_first();
    }
}

// Retrieves the first item from the list
List::Item *List::first() {
    return head_;
}

// Inserts new list item into the beginning
List::Item *List::insert(Data data)
{
    Item *new_item = new Item(data);
    if (head_) {
        new_item->next_ = head_;
        head_->prev_ = new_item;
    }
    head_ = new_item;
    if (!tail_) {
        tail_ = new_item;
    }
    return new_item;
}

// Inserts new list item after the specified item
List::Item *List::insert_after(Item *item, Data data) {
    if (!item) return nullptr;
    Item *new_item = new Item(data);
    new_item->next_ = item->next_;
    new_item->prev_ = item;
    if (item->next_) {
        item->next_->prev_ = new_item;
    }
    item->next_ = new_item;
    if (item == tail_) {
        tail_ = new_item;
    }
    return new_item;
}

// Deletes the first list item.
// Returns pointer to the item next to the deleted one.
List::Item *List::erase_first() {
    if (!head_) return nullptr;
    Item *next_item = head_->next_;
    delete head_;
    head_ = next_item;
    if (head_) {
        head_->prev_ = nullptr;
    } else {
        tail_ = nullptr;
    }
    return head_;
}

// Deletes the list item following the specified one.
// Returns pointer to the item next to the deleted one.
// Should be O(1)
List::Item *List::erase_next(Item *item) {
    if (!item || !item->next_) return nullptr;
    Item *to_erase = item->next_;
    item->next_ = to_erase->next_;
    if (to_erase->next_) {
        to_erase->next_->prev_ = item;
    }
    if (to_erase == tail_) {
        tail_ = item;
    }
    delete to_erase;
    return item->next_;
}

