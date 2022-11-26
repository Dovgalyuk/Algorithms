#include <stdlib.h>
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
    size_t length;
};

List* list_create()
{
    List* list = new List;
    list->head = nullptr;
    list->length = 0;
    return list;
}

void list_delete(List* list)
{
    ListItem* current = list->head;

    while (list->length != 0)
    {
        ListItem* prev = current;
        current = list_item_next(prev);
        list_erase(list, prev);
    }

    delete list;
}

ListItem* list_first(List* list)
{
    return list->head;
}

Data list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item->next;
}

ListItem* list_item_prev(ListItem* item)
{
    return item->prev;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* item = new ListItem;
    item->data = data;

    if (list_get_length(list)==0)
    {
        list->head = item;
        list->head->next = item;
        list->head->prev = item;
    }
    else
    {
        item->prev = list->head->prev;
        item->next = list->head;
        list->head->prev->next = item;
        list->head->prev = item;
    }
    list->head = item;
    list->length++;

    return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;

    new_item->next = item->next;
    new_item->prev = item;
    if (list_item_data(item))
    {
        item->next->prev = new_item;
    }
    item->next = new_item;
    list->length++;

    return new_item;
}

ListItem* list_erase_first(List* list)
{
    ListItem* delete_item = list->head;
    ListItem* new_head = list->head->next;

    delete_item->prev->next = new_head;
    new_head->prev = delete_item->prev;
    list->head = new_head;

    delete delete_item;
    list->length--;

    return list->head->next;
}

ListItem* list_erase(List* list, ListItem* item)
{
    ListItem* item_prev = item->prev;
    ListItem* item_next = item->next;
    if (list_item_data(item_next))
    {
        item_next->prev = item_prev;
    }
    if (list_item_data(item_prev))
    {
        item_prev->next = item->next;
    }

    if (item == list->head)
    {
        return list_erase_first(list);
    }
    delete item;
    list->length--;

    return item_next;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    return list_erase(list, item->next);
}

size_t list_get_length(const List* list)
{
    return list->length;
    
}





