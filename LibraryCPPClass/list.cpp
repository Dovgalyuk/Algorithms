#include "list.h"

List::List() : aitem(nullptr) {}

void List::copyitems(const List& a)
{
    Item* src = a.aitem;
    Item* prev = nullptr;

    while (src != nullptr)
    {
        Item* new_item = new Item(src->data(), prev, nullptr);

        if (prev)
            prev->setNext(new_item);
        else
            aitem = new_item;

        prev = new_item;
        src = src->next();
    }
}

void List::clearlist()
{
    while (aitem)
        erase_first();
}

List::List(const List& a)
{
    aitem = nullptr;
    copyitems(a);
}

List& List::operator=(const List& a)
{
    if (this != &a)
    {
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

const List::Item* List::first() const
{
    return aitem;
}

List::Item* List::insert(Data data)
{
    Item* new_item = new Item(data, nullptr, aitem);

    if (aitem)
        aitem->setPrev(new_item);

    aitem = new_item;
    return new_item;
}

List::Item* List::insert_after(Item* item, Data data)
{
    if (item == nullptr)
        return insert(data);

    Item* next = item->next();
    Item* new_item = new Item(data, item, next);

    item->setNext(new_item);
    if (next)
        next->setPrev(new_item);

    return new_item;
}

List::Item* List::erase_first()
{
    if (!aitem)
        return nullptr;

    Item* next = aitem->next();
    if (next)
        next->setPrev(nullptr);

    delete aitem;
    aitem = next;
    return aitem;
}

List::Item* List::erase_next(Item* item)
{
    if (item == nullptr)
        return erase_first();

    Item* victim = item->next();
    if (!victim)
        return nullptr;

    Item* after = victim->next();
    item->setNext(after);
    if (after)
        after->setPrev(item);

    delete victim;
    return after;
}
