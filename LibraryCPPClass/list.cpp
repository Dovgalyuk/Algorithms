#include <cstddef>
#include "list.h"

List::List() : head(nullptr)
{
}

List::List(const List &a) : head(nullptr)
{
    Item* cur = a.head;
    Item* last = nullptr;


    while (cur)
    {
        Item* node = new Item(cur->d_, nullptr);
        if (!head)
        {
            head = node;
        }
        else
        {
            last->next_ = node;
        }

        last = node;
        cur = cur->next_;

    }
}

List &List::operator=(const List &a)
{
    if (this == &a) return *this;

    while (head) erase_first();

    Item* cur = a.head;
    Item* last = nullptr;

    while (cur) {
        Item* node = new Item(cur->d_, nullptr);
        if (!head) head = node;
        else last->next_ = node;
        last = node;
        cur = cur->next_;
    }
    return *this;
}

List::~List()
{
    while (head) erase_first();
}


List::Item *List::insert(Data data)
{
    head = new Item(data, head);
    return head;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if (!item)
    {
        return insert(data);
    }

    Item* node = new Item(data, item->next_);
    item->next_ = node;
    return node;
}

List::Item *List::erase_first()
{
    if (!head)
    {
        return nullptr;
    }
    Item* next = head->next_;
    delete head;
    head = next;
    return head;
}

List::Item *List::erase_next(Item *item)
{
    if (!item)
    {
        return erase_first();
    }

    Item* target = item->next_;
    if (!target) return nullptr;

    item->next_ = target->next_;
    delete target;
    return item->next_;


}
