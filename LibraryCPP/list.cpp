#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
    ListItem* prev;
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
    return list == nullptr ? nullptr : list->first;
}

ListItem* list_last(List* list)
{
    return list == nullptr ? nullptr : list->last;
}

Data list_item_data(const ListItem* item)
{
    return item == nullptr ? Data{} : item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item == nullptr ? nullptr : item->next;
}

ListItem* list_item_prev(ListItem* item)
{
    return item == nullptr ? nullptr : item->prev;
}

ListItem* list_insert(List* list, Data data)
{
    if (list == nullptr)
        return nullptr;

    ListItem* item = new ListItem{ data, list->first, nullptr };

    if (list->first != nullptr)
    {
        list->first->prev = item;
    }
    else
    {
        list->last = item;
    }

    list->first = item;
    return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (list == nullptr)
        return nullptr;

    if (item == nullptr)
        return list_insert(list, data);

    ListItem* new_item = new ListItem{ data, item->next, item };

    if (item->next != nullptr)
    {
        item->next->prev = new_item;
    }
    else
    {
        list->last = new_item;
    }

    item->next = new_item;
    return new_item;
}

ListItem* list_erase_first(List* list)
{
    if (list == nullptr || list->first == nullptr)
        return nullptr;

    ListItem* item = list->first;
    ListItem* next = item->next;

    list->first = next;

    if (next != nullptr)
    {
        next->prev = nullptr;
    }
    else
    {
        list->last = nullptr;
    }

    delete item;
    return next;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (list == nullptr)
        return nullptr;

    if (item == nullptr)
        return list_erase_first(list);

    ListItem* to_delete = item->next;

    if (to_delete == nullptr)
        return nullptr;

    ListItem* next = to_delete->next;
    item->next = next;

    if (next != nullptr)
    {
        next->prev = item;
    }
    else
    {
        list->last = item;
    }

    delete to_delete;
    return next;
}