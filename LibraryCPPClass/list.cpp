#include "list.h"

#include <utility>

using namespace std;

List::Item::Item() : data_(Data()), next_(nullptr), prev_(nullptr), is_dummy_(true) {
    next_ = this;
    prev_ = this;
}

List::Item::Item(Data data, Item* prev, Item* next) : data_(data), next_(next), prev_(prev), is_dummy_(false) {
}

List::Item* List::Item::next() {
    if (next_->is_dummy_) {
        return nullptr;
    }
    return next_;
}

const List::Item* List::Item::next() const {
    if (next_->is_dummy_) {
        return nullptr;
    }
    return next_;
}

List::Item* List::Item::prev() {
    if (prev_->is_dummy_) {
        return nullptr;
    }
    return prev_;
}

const List::Item* List::Item::prev() const {
    if (prev_->is_dummy_) {
        return nullptr;
    }
    return prev_;
}

Data List::Item::data() const {
    return data_;
}

List::List() : dummy_(new Item()) {
}

List::List(const List& a) : dummy_(new Item()) {
    for (const Item* it = a.first(); it != nullptr; it = it->next()) {
        insert_after(last(), it->data());
    }
}

List& List::operator=(const List& a) {
    if (this == &a) {
        return *this;
    }

    List tmp(a);
    swap(dummy_, tmp.dummy_);

    return *this;
}

List::~List() {
    while (dummy_->next_ != dummy_) {
        erase_first();
    }
    delete dummy_;
}

List::Item* List::first() {
    if (dummy_->next_ == dummy_) {
        return nullptr;
    }
    return dummy_->next_;
}

const List::Item* List::first() const {
    if (dummy_->next_ == dummy_) {
        return nullptr;
    }
    return dummy_->next_;
}

List::Item* List::last() {
    if (dummy_->prev_ == dummy_) {
        return nullptr;
    }
    return dummy_->prev_;
}

const List::Item* List::last() const {
    if (dummy_->prev_ == dummy_) {
        return nullptr;
    }
    return dummy_->prev_;
}

List::Item* List::insert(Data data) {
    return insert_after(nullptr, data);
}

List::Item* List::insert_after(Item* item, Data data) {
    Item* target = (item == nullptr) ? dummy_ : item;
    Item* next_node = target->next_;
    Item* new_item = new Item(data, target, next_node);
    target->next_ = new_item;
    next_node->prev_ = new_item;
    return new_item;
}

List::Item* List::erase_first() {
    return erase_next(nullptr);
}

List::Item* List::erase_next(Item* item) {
    Item* target = (item == nullptr) ? dummy_ : item;
    Item* to_delete = target->next_;
    if (to_delete->is_dummy_) {
        return nullptr;
    }

    Item* after = to_delete->next_;
    target->next_ = after;
    after->prev_ = target;
    delete to_delete;

    if (after->is_dummy_) {
        return nullptr;
    }
    return after;
}