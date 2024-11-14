#include <cstddef>
#include "list.h"

List::List() : lHead(nullptr) {}

List::List(const List &a) : lHead(nullptr)
{
    if (!a.lHead) return;

    lHead = new Item(a.lHead->data());
    Item* current = lHead;
    Item* a_current = a.lHead->next();    

    while(a_current)
    {
        current->set_next(new Item(a_current->data()));
        current = current->next();
        a_current = a_current->next();
    }
}

List &List::operator=(const List &a)
{
    if (this != &a)
    {
        while (lHead)
        {
            erase_first();
        }

        for (Item* item = a.first(); item != nullptr; item = item->next()) 
        {
            if(!lHead)
            {
                lHead = new Item(item->data());
            }
            else
            {
                Item* current = lHead;
                while (current->next())
                {
                    current = current->next();
                }
                current->set_next(new Item(item->data()));
            }
        }
    }

    return *this;
}

List::~List()
{
    while (lHead)
    {
        erase_first();
    }
}

List::Item *List::first() const
{
    return lHead;
}

List::Item *List::insert(Data data)
{
    lHead = new Item(data, lHead);
    return lHead;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if(!item)  return nullptr;
    Item* nItem = new Item(data, item->next());
    item->set_next(nItem);
    return nItem;
}

List::Item *List::erase_first()
{
    if(!lHead) return nullptr;
    Item* oItem = lHead;
    lHead = lHead->next();
    delete oItem;
    return lHead;
}

List::Item *List::erase_next(Item *item)
{
    if(item && item->next())\
    {
        Item* ntItem = item->next();
        item->set_next(ntItem->next());
        delete ntItem;
        return item->next();
    }
    return nullptr;
}
