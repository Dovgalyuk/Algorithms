#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *next;
    ListItem *prev;
};

struct List
{
    ListItem *head;
};

List *list_create()
{
    List *list = new List;
    list->head = NULL;
    return list;
}

void list_delete(List *list)
{
    while (list->head != NULL)
    {
        list_erase_first(list);
    }
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
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
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *item = new ListItem;
    item->data = data;
    item->next = list->head;
    item->prev = NULL;
    if (list->head != NULL)
    {
        list->head->prev = item;
    }
    list->head = item;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == NULL)
    {
        return list_insert(list, data);
    }
    ListItem *new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    new_item->prev = item;
    if (item->next != NULL)
    {
        item->next->prev = new_item;
    }
    item->next = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == NULL)
    {
        return NULL;
    }
    ListItem *item = list->head;
    list->head = item->next;
    if (list->head != NULL)
    {
        list->head->prev = NULL;
    }
    ListItem *next = item->next;
    delete item;
    return next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == NULL)
    {
        return list_erase_first(list);
    }
    if (item->next == NULL)
    {
        return NULL;
    }
    ListItem *to_delete = item->next;
    item->next = to_delete->next;
    if (to_delete->next != NULL)
    {
        to_delete->next->prev = item;
    }
    ListItem *next = to_delete->next;
    delete to_delete;
    return next;
}
