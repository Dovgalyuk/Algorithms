#include <cstddef>
#include "list.h"

List::List()
{
    aitem = nullptr;
}

void List::copyitems(const List& a) {
    Item* current = a.aitem;
    Item* last_inserted = nullptr;
    while (current != nullptr) {
        Item* new_item = new Item(current->data());
        if (aitem == nullptr) {
            aitem = new_item;
        }
        else {
            last_inserted->setNext(new_item);
        }
        last_inserted = new_item;
        current = current->next();
    }
}

void List::clearlist() {
    while (aitem != nullptr) {
        erase_first();
    }
}

List::List(const List& a)
{
    copyitems(a);
}

List& List::operator=(const List& a)
{
    if (this != &a) {
        clearlist();
        copyitems(a);
    }
    return *this;
}

List::~List()
{
    clearlist();
}

List::Item* List::first()
{
    return aitem;
}

List::Item* List::insert(Data data)
{
    Item* new_item = new Item(data, aitem);
    aitem = new_item;
    return new_item;
}

List::Item* List::insert_after(Item* item, Data data)
{
    if (item == nullptr) {
        return insert(data);
    }
    Item* new_item = new Item(data, item->next());
    item->setNext(new_item);
    return new_item;
}

List::Item* List::erase_first()
{
    if (aitem == nullptr) {
        return nullptr;
    }
    Item* temp = aitem;
    aitem = aitem->next();
    Item* result = aitem;
    delete temp;
    return result;
}

List::Item* List::erase_next(Item* item)
{
    if (item == nullptr) {
        return erase_first();
    }
    if (item->next() == nullptr) {
        return nullptr;
    }
    Item* temp = item->next();
    Item* next_after_deleted = temp->next();
    item->setNext(next_after_deleted);
    delete temp;
    return next_after_deleted;
}

const List::Item* List::first() const
{
    return aitem;
}