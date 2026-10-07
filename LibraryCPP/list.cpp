#include <stdexcept>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
};

struct List
{
    ListItem *first = nullptr;
    ListItem *last = nullptr;
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    if (!list)
        return;
    while (list->first)
        list_erase_first(list);
    delete list;
}

ListItem *list_first(List *list)
{
    return list->first;
}

ListItem *list_last(List *list)
{
    return list->last;
}

Data list_item_data(const ListItem *item)
{
    if (!item)
        throw std::out_of_range("Empty list item");
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item ? item->next : nullptr;
}

ListItem *list_item_prev(ListItem *item)
{
    // A singly linked list does not store the previous item.
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, nullptr, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *next = item ? item->next : list->first;
    ListItem *inserted = new ListItem{data, next};
    if (item)
        item->next = inserted;
    else
        list->first = inserted;
    if (!next)
        list->last = inserted;
    return inserted;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, nullptr);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *erased = item ? item->next : list->first;
    if (!erased)
        return nullptr;
    ListItem *next = erased->next;
    if (item)
        item->next = next;
    else
        list->first = next;
    if (list->last == erased)
        list->last = item;
    delete erased;
    return next;
}
