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
    ListItem* last;
};

List* list_create()
{
    List* list = new List;
    list->head = nullptr;
    list->last = nullptr;
    return list;
}

void list_delete(List* list)
{
    ListItem* current = list->head;

    while (current != nullptr)
    {
        ListItem* prev = current;
        current = list_item_next(prev);
        delete prev;
        prev = nullptr;

        if (current == list->last)
        {
            delete current;
            break;
        }
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

    ListItem* current_head = list->head;
    if (current_head != nullptr)
    {
        current_head->prev = item;
        list->last->next = item;
    }
    else
    {
        list->last = item;
    }
    item->prev = list->last;
    item->next = current_head;
    list->head = item;

    return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;

    new_item->next = item->next;
    new_item->prev = item;
    if (item->next != nullptr)
    {
        item->next->prev = new_item;
    }
    item->next = new_item;
    
    return new_item;
}

ListItem* list_erase_first(List* list)
{
    ListItem* delete_item = list->head;
    ListItem* new_head = list->head->next;
    list->head = new_head;

    if (list->last != delete_item)
    {
        list->last->next = new_head;
    }

    delete delete_item;
    return nullptr;
}

ListItem* list_erase(List* list, ListItem* item)
{
    ListItem* item_prev = item->prev;
    ListItem* item_next = item->next;
    if (item_next != nullptr)
    {
        item_next->prev = item_prev;
    }
    if (item_prev != nullptr)
    {
        item_prev->next = item->next;
    }
    if (item == list->head)
    {
        list_erase_first(list);
        return nullptr;
    }
    delete item;
    return item_next;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    list_erase(list, item->next);
    return nullptr;
}

