#include "list.h"

List::List() : head_(nullptr)
{
}

void List::copy_from(const List &a) {
    clear();

    head_ = nullptr;
    Item* src = a.head_;
    Item* dst = nullptr;

    while(src) {
        Item* new_item = new Item(src->data());
        if(!head_) {
            head_ = new_item;
        } else {
            dst->set_next(new_item);
        }
        dst = new_item;
        src = src->next();
    }

}

List::List(const List &a) : head_(nullptr)
{
    copy_from(a);
}

List &List::operator=(const List &a)
{
    if(this != &a) {
        clear();
        copy_from(a);
    }
    return *this;
}

List::~List()
{
    clear();
}

void List::clear() {
    while(head_) {
        erase_first();
    }
}

List::Item *List::first() const
{
    return head_;
}

List::Item *List::insert(Data data)
{
    head_ = new Item(data, head_);
    return head_;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if(item) {
        Item* new_item = new Item(data, item->next());
        item->set_next(new_item);
        return new_item;
    }
    return nullptr;
}

List::Item *List::erase_first()
{
    if(!head_) return nullptr;
    Item* to_delete = head_;
    head_ = head_->next();
    delete to_delete;
    return head_;

}

List::Item *List::erase_next(Item *item)
{
    if(item && item->next()) {
        Item* to_delete = item->next();
        item->set_next(to_delete->next());
        delete to_delete;
        return item->next();
    }
    return nullptr;
}
