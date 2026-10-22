#include "list.h"
#include <utility>

List::List() : first_(nullptr), last_(nullptr)
{
}

List::List(const List &a) : List()
{
    try
    {
        for (Item *item = a.first_; item; item = item->next_)
        {
            insert_after(last_, item->data_);
        }
    }
    catch (...)
    {
        while (first_) erase_first();
        throw;
    }
}

List &List::operator=(const List &a)
{
    if (this != &a)
    {
        List copy(a);
        std::swap(first_, copy.first_);
        std::swap(last_, copy.last_);
    }
    return *this;
}

List::~List()
{
    while (first_) erase_first();
}

List::Item *List::first() { return first_; }
const List::Item *List::first() const { return first_; }
List::Item *List::last() { return last_; }

List::Item *List::insert(Data data)
{
    return insert_after(nullptr, data);
}

List::Item *List::insert_after(Item *item, Data data)
{
    Item *next = item ? item->next_ : first_;
    Item *added = new Item;
    added->data_ = data;
    added->prev_ = item;
    added->next_ = next;

    if (item) item->next_ = added;
    else first_ = added;

    if (next) next->prev_ = added;
    else last_ = added;

    return added;
}

List::Item *List::erase_first()
{
    return erase_next(nullptr);
}

List::Item *List::erase_next(Item *item)
{
    Item *removed = item ? item->next_ : first_;
    if (!removed) return nullptr;

    Item *next = removed->next_;
    if (item) item->next_ = next;
    else first_ = next;

    if (next) next->prev_ = item;
    else last_ = item;

    delete removed;
    return next;
}
