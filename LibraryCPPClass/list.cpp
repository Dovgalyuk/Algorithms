#include <cstddef>
#include "list.h"

List::List() : head(nullptr), tail(nullptr)
{
}

List::List(const List &a) : head(nullptr), tail(nullptr)
{
    copy_from(a);
}

List &List::operator=(const List &a)
{
    if (this != &a) {
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
    while (head)
        erase_first();
}

void List::copy_from(const List& a) {
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
    tail = last;
}


List::Item *List::insert(Data data)
{
    head = new Item(data, head);
    if (!tail)
        tail = head;
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
    if (item == tail)
        tail = node;
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
    if (!head)
        tail = nullptr;
    return head;
}

List::Item *List::erase_next(Item *item)
{
    if (!item)
    {
        return erase_first();
    }

    Item* target = item->next_;
    if (!target) 
        return nullptr;

    item->next_ = target->next_;

    if (target == tail)
        tail = item;

    delete target;
    return item->next_;


}
List::Item* List::last() const {
    return tail;
}
