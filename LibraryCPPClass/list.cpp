
#include "list.h"

// Создание пустого списка
List::List()
{
    head_ = nullptr;
    tail_ = nullptr;
}

// Копирование списка
List::List(const List &a) : List()
{
    for (Item *p = a.head_; p != nullptr; p = p->next_)
    {
        insert_after(tail_, p->value_);
    }
}

// Присваивание одного списка другому
List &List::operator=(const List &a)
{
    if (this == &a)
        return *this;

    while (head_ != nullptr)
        erase_first();

    for (Item *p = a.head_; p != nullptr; p = p->next_)
    {
        insert_after(tail_, p->value_);
    }

    return *this;
}

// Удаление всего списка
List::~List()
{
    while (head_ != nullptr)
        erase_first();
}

// Получение первого элемента
List::Item *List::first()
{
    return head_;
}

// Получение первого элемента без изменения списка
const List::Item *List::first() const
{
    return head_;
}

// Получение последнего элемента
List::Item *List::last()
{
    return tail_;
}

// Добавление элемента в начало
List::Item *List::insert(Data data)
{
    Item *p = new Item(data);

    p->next_ = head_;

    if (head_ != nullptr)
        head_->prev_ = p;
    else
        tail_ = p;

    head_ = p;
    return p;
}

// Добавление элемента после указанного
List::Item *List::insert_after(Item *item, Data data)
{
    if (item == nullptr)
        return insert(data);

    Item *p = new Item(data);

    p->prev_ = item;
    p->next_ = item->next_;

    if (item->next_ != nullptr)
        item->next_->prev_ = p;
    else
        tail_ = p;

    item->next_ = p;
    return p;
}

// Удаление первого элемента
List::Item *List::erase_first()
{
    if (head_ == nullptr)
        return nullptr;

    Item *p = head_->next_;
    delete head_;

    head_ = p;

    if (head_ != nullptr)
        head_->prev_ = nullptr;
    else
        tail_ = nullptr;

    return head_;
}

// Удаление элемента после указанного
List::Item *List::erase_next(Item *item)
{
    if (item == nullptr)
        return erase_first();

    if (item->next_ == nullptr)
        return nullptr;

    Item *p = item->next_;
    Item *next = p->next_;

    item->next_ = next;

    if (next != nullptr)
        next->prev_ = item;
    else
        tail_ = item;

    delete p;
    return next;
}
