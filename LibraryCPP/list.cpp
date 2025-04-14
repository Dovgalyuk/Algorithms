#include <cstddef>
#include "list.h"
#include <iostream>

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* head;
    ListItem* end;
};

List *list_create()
{
    List* list = new List;
    list->head = nullptr;
    list->end = nullptr;
    return list;
}

void list_delete(List *list)
{
    ListItem* current = list->head;
    while (current != nullptr)
    {
        ListItem* next = current->next;
        delete current;
        current = next;
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

ListItem *list_insert(List *list, Data data)
{
    ListItem* item = new ListItem;
    item->data=data;
    item->next=list->head;

    if(list->head == nullptr){
        list->end = item;
    }

    list->head = item;
    return item;
}

ListItem* list_insert_end(List* list, Data data) 
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = nullptr;

    if (list->head == nullptr)
    {
        list->head = new_item;
    }
    else
    {
        list->end->next = new_item;
    }

    list->end = new_item;
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr)
    {
        return nullptr;
    }

    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    item->next = new_item;

    if (item == list->end)
    {
        list->end = new_item;
    }

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr)
    {
        return nullptr;
    }

    ListItem* item = list->head;
    list->head = item->next;

    if (list->head == nullptr)
    {
        list->end = nullptr;
    }

    delete item;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr || item->next == nullptr)
    {
        return nullptr;
    }

    ListItem* to_delete = item->next;
    item->next = to_delete->next;

    if (to_delete == list->end)
    {
        list->end = item;
    }

    delete to_delete;
    return item->next;
}
