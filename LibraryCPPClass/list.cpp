#include <cstddef>
#include "list.h"

List::List()
{
    _first = nullptr;
}

List::List(const List &a)
{
    _first = nullptr;
    Item* current = a._first;
    while(current != nullptr){
        insert(current->data());
        current = current->next();
    }
}

List &List::operator=(const List &a)
{
    if (this != &a){
        while (_first != nullptr){
            erase_first();
        } 
    

        Item* current = a._first;
        while(current != nullptr){
            insert(current->data());
            current = current->next();
        }
    }
    return *this;
}

List::~List()
{
    while (_first != nullptr)
    {
        erase_first();
    }   
}

List::Item *List::first()
{
    return _first;
}

List::Item *List::insert(Data data)
{
    Item* newItem = new Item(data, _first);
    _first = newItem;

    return newItem;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if(item == nullptr){
        return insert(data);
    }

    Item* newItem = new Item(data, item->next());
    item->SetNext(newItem);

    return newItem;
}

List::Item *List::erase_first()
{
    if(_first == nullptr){
        return nullptr;
    }

    Item* nextItem = _first->next();
    delete _first;
    _first = nextItem;

    return nextItem;
}

List::Item *List::erase_next(Item *item)
{
    if (item == nullptr){
        return erase_first();
    }

    Item* toDelete = item->next();
    if (toDelete == nullptr){
        return nullptr;
    }

    Item* nextAfterDelete = toDelete->next();
    item->SetNext(nextAfterDelete);

    delete toDelete;
    return nextAfterDelete;
}
