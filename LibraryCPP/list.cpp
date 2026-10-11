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
    ListItem *tail;
};

List *list_create()
{
    List *list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

void list_delete(List *list)
{
    if (!list) return;
    ListItem *curr = list->head;
    while (curr)
    {
        ListItem *next = curr->next;
        delete curr;
        curr = next;
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list ? list->head : nullptr;
}

ListItem *list_last(List *list)
{
    return list ? list->tail : nullptr;
}

Data list_item_data(const ListItem *item)
{
    return item ? item->data : (Data)0;
}

ListItem *list_item_next(ListItem *item)
{
    return item ? item->next : nullptr;
}

ListItem *list_item_prev(ListItem *item)
{
    (void)item;
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    if (!list) return nullptr;
    ListItem *item = new ListItem;
    item->data = data;
    item->next = list->head;
    list->head = item;
    if (!list->tail)
    {
        list->tail = item;
    }
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list) return nullptr;
    if (!item)
    {
        return list_insert(list, data);
    }
    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    item->next = new_item;
    if (list->tail == item)
    {
        list->tail = new_item;
    }
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (!list || !list->head) return nullptr;
    ListItem *to_delete = list->head;
    ListItem *next = to_delete->next;
    list->head = next;
    if (list->tail == to_delete)
    {
        list->tail = nullptr;
    }
    delete to_delete;
    return next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list) return nullptr;
    if (!item)
    {
        return list_erase_first(list);
    }
    if (!item->next) return nullptr;
    ListItem *to_delete = item->next;
    ListItem *next = to_delete->next;
    item->next = next;
    if (list->tail == to_delete)
    {
        list->tail = item;
    }
    delete to_delete;
    return next;
}
