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
    if (!list) return NULL;
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    if (!item) return (Data)0;
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (!item) return NULL;
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (!item) return NULL;
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *newItem = new ListItem;
    newItem->data = data;
    newItem->prev = NULL;
    newItem->next = list->head;

    if (list->head != NULL)
    {
        list->head->prev = newItem;
    }
    
    list->head = newItem;
    return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == NULL)
    {
        return list_insert(list, data);
    }

    ListItem *newItem = new ListItem;
    newItem->data = data;
    newItem->prev = item;
    newItem->next = item->next;

    if (item->next != NULL)
    {
        item->next->prev = newItem;
    }
    
    item->next = newItem;
    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (!list || !list->head) return NULL;

    ListItem *itemToErase = list->head;
    ListItem *newHead = itemToErase->next;

    list->head = newHead;

    if (newHead != NULL)
    {
        newHead->prev = NULL;
    }

    delete itemToErase;
    return newHead;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == NULL)
    {
        return list_erase_first(list);
    }

    ListItem *itemToErase = item->next;
    if (itemToErase == NULL)
    {
        return NULL;
    }

    ListItem *itemAfterErased = itemToErase->next;
    
    item->next = itemAfterErased;
    if (itemAfterErased != NULL)
    {
        itemAfterErased->prev = item;
    }

    delete itemToErase;
    return itemAfterErased;
}
