#include <cstddef>
#include "list.h"
#include <utility>

List::List() : head_(nullptr), tail_(nullptr)
{
}

List::List(const List &a) : head_(nullptr), tail_(nullptr)
{
    Item* last_added = nullptr;
    for (Item* item = a.head_; item != nullptr; item = item->next_) {
        last_added = insert_after(last_added, item->data_);
    }
}

List &List::operator=(const List &a)
{
    if (this == &a) {
        return *this;
    }
        
    List temp(a);
    std::swap(head_, temp.head_);
    std::swap(tail_, temp.tail_);
    return *this;
}

List::~List()
{
    Item* current = head_;
    while (current != nullptr) {
        Item* next = current->next_;
        delete current;
        current = next;
    }
}

List::Item *List::first() const
{
    return head_;
}

List::Item *List::last() const
{
    return tail_;
}

List::Item *List::insert(Data data)
{
    Item* new_item = new Item;
    new_item->data_ = data;
    new_item->next_ = head_;
    new_item->prev_ = nullptr;

    if (head_ != nullptr) {
        head_->prev_ = new_item;
    }
    head_ = new_item;

    if (tail_ == nullptr) {
        tail_ = new_item;
    }
    return new_item;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if (item == nullptr) {
        return insert(data);
    }
    
    Item* new_item = new Item;
    new_item->data_ = data;
    new_item->next_ = item->next_;
    new_item->prev_ = item;

    if (item->next_ != nullptr) {
        item->next_->prev_ = new_item;
    }
    else {
        tail_ = new_item;
    }
    item->next_ = new_item;

    return new_item;

}

List::Item *List::erase_first()
{
    if (head_ == nullptr) {
        return nullptr;
    }

    Item* next = head_->next_;

    if (next != nullptr) {
        next->prev_ = nullptr;
    }
    else {
        tail_ = nullptr;
    }

    delete head_;
    head_ = next;
    return next;
}

List::Item *List::erase_next(Item *item)
{
    Item* target = (item == nullptr) ? head_ : item->next_;
    if (target == nullptr) {
        return nullptr;
    }

    Item* next = target->next_;

    if (item == nullptr) {
        if (next != nullptr) {
            next->prev_ = nullptr;
        }
        else {
            tail_ = nullptr;
        }
        head_ = next;
    } else {
        item->next_ = next;
        if (next != nullptr) {
            next->prev_ = item;
        }
        else {
            tail_ = item;
        }
    }

    delete target;
    return next;
}
