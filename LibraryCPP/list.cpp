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
    ListItem *first;
};

List *list_create()
{
    List *newList = new List;
    newList->first = NULL;
    return newList;
    return new List;
}

void list_delete(List *list)
{
    ListItem *current = list->first;
    while (current != NULL)
    {
        ListItem *next = current->next;
        delete current;
        current = next;
    }
    // TODO: free items
    delete list;
}

ListItem *list_first(List *list)
{
    return list->first;
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
    ListItem *newItem = new ListItem;
    newItem->data = data;
    newItem->prev = NULL;
    newItem->next = list->first;

    if (list->first != NULL)
    {
        list->first->prev = newItem;
    }

    list->first = newItem;

    return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == NULL)
    {
        return NULL; 
    }

    ListItem *newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    newItem->prev = item;

    if (item->next != NULL)
    {
        item->next->prev = newItem;
    }

    item->next = newItem;

    return newItem;
}

ListItem *list_erase_first(List *list)
{
    ListItem *firstItem = list->first;

    if (firstItem != NULL)
    {
        list->first = firstItem->next;

        if (list->first != NULL)
        {
            list->first->prev = NULL;
        }

        delete firstItem;
    }

    return list->first;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == NULL || item->next == NULL)
    {
        return NULL; 
    }

    ListItem *nextItem = item->next;
    item->next = nextItem->next;

    if (nextItem->next != NULL)
    {
        nextItem->next->prev = item;
    }

    delete nextItem;

    return item->next;
}