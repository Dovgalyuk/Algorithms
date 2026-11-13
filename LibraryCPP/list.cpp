#include <cstddef>
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
    list->first = NULL;
    list->last = NULL;
    return list;
}

void list_delete(List *list)
{
    ListItem *item = list->first;
    while (item != NULL)
    {
        ListItem *next = item->next;
        delete item;
        item = next;
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
    return NULL;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *insert = new ListItem;
    insert->data = data;
    insert->next = list->first;
    list->first = insert;
    if (list->last == NULL)
    {
        list->last = insert;
    }
    return insert;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == NULL)
    {
        return list_insert(list, data);
    }

    ListItem *insert = new ListItem;
    insert->data = data;
    insert->next = item->next;
    item->next = insert;
    if (list->last == item)
    {
        list->last = insert;
    }
    return insert;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, NULL);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *erase;
    if (item != NULL)
    {
        erase = item->next;
    } 
    else
    {
        erase = list->first;
    }
        
    if (erase == NULL)
    {
        return NULL;
    }
        
    if (item != NULL)
    {
        item->next = erase->next;
    }
    else
    {
        list->first = erase->next;
    }
        
    if (list->last == erase)
    {
        if (item != NULL)
        {
            list->last = item;
        }
        else
        {
            list->last = list->first;
        } 
    }

    delete erase;

    if (item != NULL)
    {
        return item->next;
    } 
    else
    {
        return list->first;
    }
}
