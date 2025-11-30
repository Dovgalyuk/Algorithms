#include <cstddef>
#include "list.h"

struct ListItem;

struct List;

List *list_create()
{
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void list_delete(List *list)
{
    ListItem* cur = list->head;
    while (cur)
    {
        ListItem* next = cur->next;
        delete cur;
        cur = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
}


Data list_item_data(const ListItem *item)
{
    return item->value;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* item = new ListItem;
    item->value = data;

    item->prev = nullptr;
    item->next = list->head;

    if (list->head)
        list->head->prev = item;
    else
        list->tail = item;

    list->head = item;
    return item;
}

ListItem* list_insert_after(List* list, ListItem* pos, Data data)
{
    if (!pos) return list_insert(list, data);

    ListItem* item = new ListItem;
    item->value = data;

    item->next = pos->next;
    item->prev = pos;

    if (pos->next)
        pos->next->prev = item;
    else
        list->tail = item;

    pos->next = item;
    return item;
}

ListItem *list_erase_first(List *list)
{
    if (!list->head)
        return nullptr;

    ListItem* item = list->head;
    ListItem* next = item->next;

    if (next)
        next->prev = nullptr;
    else
        list->tail = nullptr;

    delete item;

    list->head = next;
    return next;
}

ListItem *list_erase_next(List *list, ListItem *pos)
{
    if (!pos || !pos->next)
        return nullptr;

    ListItem* item = pos->next;
    ListItem* next = item->next;

    pos->next = next;

    if (next)
        next->prev = pos;
    else
        list->tail = pos;

    delete item;
    return next;
}
