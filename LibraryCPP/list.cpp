#include "list.h"

struct ListItem
{
    ListItem *prev;
    ListItem *next;
    Data data;
    bool is_sentinel;
};

struct List
{
    ListItem sentinel{&sentinel, &sentinel, 0, true};
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    if (!list)
        return;

    while (list_first(list))
        list_erase_first(list);

    delete list;
}

ListItem *list_first(List *list)
{
    return list_item_next(&list->sentinel);
}

ListItem *list_last(List *list)
{
    return list_item_prev(&list->sentinel);
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next->is_sentinel ? nullptr : item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->prev->is_sentinel ? nullptr : item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, nullptr, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!item)
        item = &list->sentinel;

    ListItem *next = item->next;
    ListItem *inserted = new ListItem{item, next, data, false};
    item->next = inserted;
    next->prev = inserted;
    return inserted;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, nullptr);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!item)
        item = &list->sentinel;

    ListItem *erased = item->next;
    if (erased->is_sentinel)
        return nullptr;

    ListItem *next = erased->next;
    item->next = next;
    next->prev = item;
    delete erased;
    return next->is_sentinel ? nullptr : next;
}
