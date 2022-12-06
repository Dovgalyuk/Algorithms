#include <cstddef>
#include "list.h"

struct ListItem
{
    Data field;
    ListItem* next;
    ListItem* prev;
};

struct List
{
    ListItem* first;
    ListItem* last;
};

List* list_create()
{
    List* list = new List;
    list->first = nullptr;
    list->last = nullptr;
    return list;
}

void list_delete(List* list)
{
    while (list->first != list->last)
    {
        ListItem* temp = list->first;
        list->first = list->first->next;
        delete temp;
    }
    delete list->first;
    delete list;
}

ListItem* list_first(List* list)
{
    return list->first;
}
ListItem* list_last(List* list)
{
    return list->last;
}
Data list_item_data(const ListItem* item)
{
    if (item)
    {
        return item->field;
    }
    else
    {
        return Data();
    }
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
    ListItem* ins = new ListItem;
    ins->field = data;
    if (list->first)
    {
        ins->next = list->first;
        list->first->prev = ins;
    }
    else
    {
        list->last = ins;
    }
    ins->prev = list->last;
    list->last->next = ins;
    list->first = ins;
    return ins;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* newItem = new ListItem;
    newItem->field = data;
    if (item == list->first)
    {
        newItem->prev = list->first;
        newItem->next = list->first->next;
        list->first->next = newItem;
        return newItem;
    }
    if (item == list->last)
    {
        newItem->prev = list->last;
        newItem->next = list->last->next;
        list->last->next = newItem;
        return newItem;
    }
    else
    {
        newItem->prev = item;
        newItem->next = item->next;
        item->next = newItem;
        return newItem;
    }
}
ListItem* list_erase(List* list, ListItem* item)
{
    ListItem* erase = nullptr;
    if (list->first)
    {
        if (item->next == item)
        {
            list->first = nullptr;
            list->last = nullptr;
            erase = item;
            delete erase;
        }
        else
        {
            if (item == list->last)
            {
                erase = list->last;
                list->last = list->last->prev;
            }
            if (item == list->first)
            {
                erase = list->first;
                list->first = list->first->next;
            }
            (item->next)->prev = item->prev;
            (item->prev)->next = item->next;
            delete erase;
            return item;
        }
    }
    else
    {
        return NULL;
    }
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    list_erase(list, list_item_next(item));
    return item;
}


