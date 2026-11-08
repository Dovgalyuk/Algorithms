
#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* first;
    ListItem* last;
};

List* list_create()
{
    List* list = new List;
    list->first = nullptr;
    list->last = nullptr;
    return list;
}

void list_delete(List* list)
{
    if (list == nullptr)
        return;

    ListItem* item = list->first;

    while (item != nullptr)
    {
        ListItem* next = item->next;
        delete item;
        item = next;
    }

    delete list;
}

ListItem* list_first(List* list)
{
    return list != nullptr ? list->first : nullptr;
}

ListItem* list_last(List* list)
{
    return list != nullptr ? list->last : nullptr;
}

Data list_item_data(const ListItem* item)
{
    return item != nullptr ? item->data : Data{};
}

ListItem* list_item_next(ListItem* item)
{
    return item != nullptr ? item->next : nullptr;
}

ListItem* list_item_prev(ListItem* item)
{
    (void)item;
    return nullptr;
}

ListItem* list_insert(List* list, Data data)
{
    if (list == nullptr)
        return nullptr;

    ListItem* item = new ListItem{ data, list->first };
    list->first = item;

    if (list->last == nullptr)
        list->last = item;

    return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (list == nullptr)
        return nullptr;

    if (item == nullptr)
        return list_insert(list, data);

    ListItem* newItem = new ListItem{ data, item->next };
    item->next = newItem;

    if (list->last == item)
        list->last = newItem;

    return newItem;
}

ListItem* list_erase_first(List* list)
{
    if (list == nullptr || list->first == nullptr)
        return nullptr;

    ListItem* removed = list->first;
    ListItem* next = removed->next;

    list->first = next;

    if (next == nullptr)
        list->last = nullptr;

    delete removed;
    return next;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (list == nullptr)
        return nullptr;

    if (item == nullptr)
        return list_erase_first(list);

    ListItem* removed = item->next;

    if (removed == nullptr)
        return nullptr;

    item->next = removed->next;

    if (list->last == removed)
        list->last = item;

    ListItem* next = removed->next;
    delete removed;

    return next;
}

