#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
};

struct List
{
    ListItem *first;
    ListItem *last;
};

List *list_create()
{
    List *list = new List;
    list->first = nullptr;
    list->last = nullptr;
    return list;
}

void list_delete(List *list)
{
    while (list->first != nullptr)
    {
        list_erase_first(list);
    }
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
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *item = new ListItem;
    item->data = data;
    item->next = list->first;
    list->first = item;
    if (list->last == nullptr)
    {
        list->last = item;
    }
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr)
    {
        return list_insert(list, data);
    }
    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    item->next = new_item;
    if (list->last == item)
    {
        list->last = new_item;
    }
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->first == nullptr)
    {
        return nullptr;
    }
    ListItem *item = list->first;
    list->first = item->next;
    if (list->first == nullptr)
    {
        list->last = nullptr;
    }
    delete item;
    return list->first;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr)
    {
        return list_erase_first(list);
    }
    ListItem *to_delete = item->next;
    if (to_delete == nullptr)
    {
        return nullptr;
    }
    item->next = to_delete->next;
    if (list->last == to_delete)
    {
        list->last = item;
    }
    delete to_delete;
    return item->next;
}