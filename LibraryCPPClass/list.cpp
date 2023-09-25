#include <cstddef>
#include "list.h"

List::List()
{
}

List::List(const List &a)
{
}

List &List::operator=(const List &a)
{
    return *this;
}

List::~List()
{
}

List::Item *List::first()
{
    return nullptr;
}

List::Item *List::insert(Data data)
{
    return nullptr;
}

List::Item *List::insert_after(Item *item, Data data)
{
    return nullptr;
}

List::Item *List::erase_first()
{
    return nullptr;
}

List::Item *List::erase_next(Item *item)
{
    return nullptr;
}
