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
    List()
    {
        first = 0;
        last = 0;
    }
    ~List()
    {
        while (first != last)
        {
            ListItem* temp = first;
            first = first->prev;
            delete temp;
        }
        delete last;
        delete first;
    }
};

List* list_create()
{
    return new List;
}

void list_delete(List * list)
{
    delete list;
}

ListItem* list_first(List* list)
{
    return list->first;
}
ListItem* list_last(List* list)
{
    return list->first;
}
Data list_item_data(const ListItem* item)
{

        return item->field;

}

ListItem* list_item_next(ListItem* item)
{
        return item->prev;
}

ListItem* list_item_prev(ListItem* item)
{
    return item->next;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* ins = new ListItem;
    ins->field = data;
    if (list->first)
    {
        ins->prev = list->first;
        list->first->next = ins;
    }
    else
    {
        list->last = ins;
    }
    ins->next = list->last;
    list->last->prev = ins;
    list->first = ins;
    return ins;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* newItem = new ListItem;
    newItem->field = data;
    if (item == list->first)
    {
        newItem->next = list->first;
        newItem->prev = list->first->prev;
        list->first->prev = newItem;
        return newItem;
    }
    if (item == list->last)
    {
        newItem->next = list->last;
        newItem->prev = list->last->prev;
        list->last->prev = newItem;
        return newItem;
    }
    else
    {
        newItem->next = item;
        newItem->prev = item->prev;
        item->prev = newItem;
        return newItem;
    }
}
ListItem* list_erase(List* list, ListItem* item)
{
    if (list->first)
    {
        if (item->next == item)
        {
            list->first = NULL;
            list->last = NULL;
        }
        else
        {
            if (item == list->last)
            {
                list->last = list->last->next;
            }
            if (item == list->first)
            {
                list->first = list->first->prev;
            }
            (item->next)->prev = item->prev;
            (item->prev)->next = item->next;
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
    ListItem* erase = nullptr;
    if (list->first == nullptr) {
        return erase;
    }
    if (item->next == nullptr) {
        return erase;
    }
    erase = item->next;

    item->next = item->next->next;

    delete erase;
    return item->next;
}

