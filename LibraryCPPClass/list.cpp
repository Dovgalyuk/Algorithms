#include <cstddef>
#include "list.h"

List::List()
{
    _first = nullptr;
}

List::List(const List &a)
{
    _first = nullptr;
    Item** ppNext = &_first;
    Item* current = a._first;
    
    while (current != nullptr) {
        *ppNext = new Item(current->data()); 
        ppNext = &((*ppNext)->next_ref()); 
        current = current->next();
    }
    *ppNext = nullptr; 
}



List &List::operator=(const List &a)
{
    if (this != &a)
    {
        List temp(a);

        Item* tm = _first;
        _first = temp._first;
        temp._first = tm;
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
    _size++;
    return newItem;
}

List::Item *List::insert(int data)
{
    Data temp = std::to_string(data);

    return insert(temp);
}

List::Item *List::insert_after(Item *item, Data data)
{
    if(item == nullptr)
    {
        return insert(data);
    }

    Item* newItem = new Item(data, item->next());
    item->SetNext(newItem);

    _size++;
    return newItem;
}

List::Item *List::insert_after(Item *item, int data)
{
    Data temp = std::to_string(data);
    return insert_after(item, temp);
}

List::Item *List::erase_first()
{
    if(_first == nullptr)
    {
        return nullptr;
    }

    Item* nextItem = _first->next();
    delete _first;
    _first = nextItem;

    _size--;
    return nextItem;
}

List::Item *List::erase_next(Item *item)
{
    if (item == nullptr)
    {
        return erase_first();
    }

    Item* toDelete = item->next();
    if (toDelete == nullptr)
    {
        return nullptr;
    }

    Item* nextAfterDelete = toDelete->next();
    item->SetNext(nextAfterDelete);

    _size--;
    delete toDelete;
    return nextAfterDelete;
}

size_t List::Size(){
    return _size;
}
