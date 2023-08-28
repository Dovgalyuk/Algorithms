#include <cstddef>
#include "list.h"

List::List()
{
}

List::List(const List &a)
{
    // implement or disable this function
}

List &List::operator=(const List &a)
{
    // implement or disable this function
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
