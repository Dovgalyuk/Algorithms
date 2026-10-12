#include <cstddef>
#include "list.h"

List::List()
    : first_(nullptr), last_(nullptr)
{
}

List::List(const List& a)
    : first_(nullptr), last_(nullptr)
{
    copy_from(a);
}

List& List::operator=(const List& a)
{
    if (this == &a)
        return *this;

    clear();
    copy_from(a);
    return *this;
}

List::~List()
{
    clear();
}

List::Item* List::first()
{
    return first_;
}

const List::Item* List::first() const
{
    return first_;
}

List::Item* List::last()
{
    return last_;
}

List::Item* List::insert(Data data)
{
    Item* item = new Item(data, nullptr, first_);
    if (first_ != nullptr)
        first_->prev_ = item;
    else
        last_ = item; // список был пустым, новый элемент ещё и последний
    first_ = item;
    return item;
}

List::Item* List::insert_after(Item* item, Data data)
{
    if (item == nullptr)
        return insert(data);

    Item* added = new Item(data, item, item->next_);
    if (item->next_ != nullptr)
        item->next_->prev_ = added;
    else
        last_ = added; // вставили после последнего элемента
    item->next_ = added;
    return added;
}

List::Item* List::erase_first()
{
    if (first_ == nullptr)
        return nullptr;

    Item* next = first_->next_;
    delete first_;
    first_ = next;
    if (first_ != nullptr)
        first_->prev_ = nullptr;
    else
        last_ = nullptr; // удалили единственный элемент
    return first_;
}

List::Item* List::erase_next(Item* item)
{
    if (item == nullptr)
        return erase_first();

    Item* removed = item->next_;
    if (removed == nullptr)
        return nullptr;

    Item* next = removed->next_;
    delete removed;
    item->next_ = next;
    if (next != nullptr)
        next->prev_ = item;
    else
        last_ = item; // удалили последний элемент
    return next;
}

void List::clear()
{
    while (first_ != nullptr)
        erase_first();
}

void List::copy_from(const List& a)
{
    // идём по чужому списку с начала и добавляем копии в конец своего
    Item* tail = nullptr;
    for (const Item* item = a.first_; item != nullptr; item = item->next_)
        tail = insert_after(tail, item->data_);
}