#include <cstddef>
#include "list.h"

List::List()
{
    _first = nullptr;
}

void List::copy_recursive(Item* current)
{
    if (current == nullptr) return;
    
    // Сначала копируем хвост списка
    copy_recursive(current->next());
    // Затем вставляем текущий элемент (в обратном порядке)
    insert(current->data());
}

List::List(const List &a)
{
    _first = nullptr;
    copy_recursive(a._first);
}



List &List::operator=(const List &a)
{
    if (this != &a)
    {
        List temp(a);  // Конструктор копирования создает правильный порядок

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

    return newItem;
}

List::Item *List::insert_after(Item *item, Data data)
{
    if(item == nullptr)
    {
        return insert(data);
    }

    Item* newItem = new Item(data, item->next());
    item->SetNext(newItem);

    return newItem;
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

    delete toDelete;
    return nextAfterDelete;
}
