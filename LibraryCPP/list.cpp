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
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List *list)
{
    while (list->head != nullptr) 
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
    ListItem* item = new ListItem;
    item->data = data;
    item->next = list->head;
    item->prev = nullptr;

    if (list->head != nullptr) 
    {
        list->head->prev = item;
    }
    list->head = item;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr) 
    {
        return list_insert(list, data);
    }

    ListItem* item = new ListItem;
    item->data = data;
    item->next = item->next;
    item->prev = item;

    if (item->next != nullptr) 
    {
        item->next->prev = new_item;
    }
    item->next = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr) 
    {
        return nullptr;
    }

    ListItem* next = list->head->next;
    delete list->head;
    list->head = next;

    if (next != nullptr) 
    {
        next->prev = nullptr;
    }

    return next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!item) 
    {
        return list_erase_first(list);
    }
    
    if (!item->next) 
    {
        return nullptr;
    }
    
    ListItem* next = item->next->next;
    delete item->next;
    item->next = next;
    return next;
}