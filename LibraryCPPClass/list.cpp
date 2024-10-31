#include "list.h"

List::List(const List& a) : head_(nullptr)
{
    for (Item* item = a.first(); item != nullptr; item = item->next())
        insert(item->data());
}

List& List::operator=(const List& a)
{
    if (this != &a) {
        while (head_)
            erase_first();
        for (Item* item = a.first(); item != nullptr; item = item->next())
            insert(item->data());
    }
    return *this;
}

List::~List()
{
    while (head_)
        erase_first();
}

List::Item* List::insert(Data data)
{
    head_ = new Item(data, head_);
    return head_;
}

List::Item* List::insert_after(Item* item, Data data)
{
    if (!item) return nullptr;
    item->set_next(new Item(data, item->next()));
    return item->next();
}

List::Item* List::erase_first()
{
    if (!head_) return nullptr;
    Item* temp = head_;
    head_ = head_->next();
    delete temp;
    return head_;
}

List::Item* List::erase_next(Item* item)
{
    if (!item || !item->next()) return nullptr;
    Item* temp = item->next();
    item->set_next(temp->next());
    delete temp;
    return item->next();
}
