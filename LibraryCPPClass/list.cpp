#include <cstddef>
#include "list.h"

List::List()
{
    head = nullptr;
    tail = nullptr;
}

List::List(const List &a)
{
    head = nullptr;
    tail = nullptr;
    for (Item *item = a.head; item != nullptr; item = item->next()) {
        insert_after(tail, item->data());
    }
}

List &List::operator=(const List &a)
{
    List copy(a);

    Item *temp_head = head;
    head = copy.head;
    copy.head = temp_head;

    Item *temp_tail = tail;
    tail = copy.tail;
    copy.tail = temp_tail;
    return *this;
}

List::~List()
{
    while (head != nullptr) {
        erase_first();
    }
}

List::Item *List::first()
{
    return head;
}

List::Item *List::last()
{
    return tail;
}

List::Item *List::insert(Data data)
{
    Item *new_item = new Item(data, nullptr, head);
    if (head != nullptr) {
        head->prev_item = new_item;
    } else {
        tail = new_item;
    }
    head = new_item;
    return new_item;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if (item == nullptr) {
        return insert(data);
    }
    Item *new_item = new Item(data, item, item->next_item);
    if (item->next_item != nullptr) {
        item->next_item->prev_item = new_item;
    } else {
        tail = new_item;
    }
    item->next_item = new_item;
    return new_item;
}

List::Item *List::erase_first()
{
    if (head == nullptr) {
        return nullptr;
    }
    Item *to_delete = head;
    Item *next = head->next_item;
    head = next;
    if (head != nullptr) {
        head->prev_item = nullptr;
    } else {
        tail = nullptr;
    }
    delete to_delete;
    return head;
}

List::Item *List::erase_next(Item *item)
{
    if (item == nullptr) {
        return erase_first();
    }
    Item *to_delete = item->next_item;
    if (to_delete == nullptr) {
        return nullptr;
    }
    Item *next = to_delete->next_item;
    item->next_item = next;
    if (next != nullptr) {
        next->prev_item = item;
    } else {
        tail = item;
    }
    delete to_delete;
    return next;
}
