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
    ListItem* head;
};

List *list_create()
{
    List* temp = new List;
    temp->head = NULL;
    return temp;
}

void list_delete(List *list)
{
    // TODO: free items
    ListItem* cur = list->head;
    ListItem* next;
    while (cur)
    {
        next = cur->next;
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
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->prev = NULL;
    if (list->head)
    {
        newItem->next = list->head;
        list->head->prev = newItem;
    }
    else
        newItem->next = NULL;
    list->head = newItem;
    return list->head;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    if (item->next) item->next->prev = newItem;
    newItem->prev = item;
    item->next = newItem;
    return list->head;
}

ListItem *list_erase_first(List *list)
{
    ListItem* next = list->head->next;
    delete list->head;
    list->head = next;
    if(next) next->prev = NULL;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item->next)
    {
        ListItem* next = item->next;
        item->next = next->next;
        if (next->next) next->next->prev = item;
        delete next;
    }
    return list->head;
}