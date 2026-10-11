#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
};

struct List
{
    ListItem *head;
    ListItem *last;
};

List *list_create()
{
    List *list = new List;
    list->head = nullptr;
    list->last = nullptr;
    return list;
}

void list_delete(List *list)
{
    ListItem *current = list->head;
    while (current != nullptr)
    {
        ListItem *next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
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

ListItem *list_item_prev(ListItem *)
{
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *item = new ListItem;
    item->data = data;
    item->next = list->head;
    list->head = item;
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
    if (item == list->last)
    {
        list->last = new_item;
    }
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr)
    {
        return nullptr;
    }
    ListItem *to_delete = list->head;
    list->head = to_delete->next;
    if (list->head == nullptr)
    {
        list->last = nullptr;
    }
    delete to_delete;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr)
    {
        return list_erase_first(list);
    }
    if (item->next == nullptr)
    {
        return nullptr;
    }
    ListItem *to_delete = item->next;
    item->next = to_delete->next;
    if (to_delete == list->last)
    {
        list->last = item;
    }
    delete to_delete;
    return item->next;
}

