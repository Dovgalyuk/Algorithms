#include <cstddef>
#include "list.h"

struct ListItem
{
    Data field;
    ListItem* next; 
    ListItem* prev; 
    ListItem()
    {
        field = NULL;
        prev = nullptr;
        next = nullptr;
    }
};

struct List
{
    ListItem* first;
    ListItem* last;
    List()
    {
        first = nullptr;
        last = nullptr;
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
    }
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    delete list;
}

ListItem *list_first(List *list)
{
    return list->first;
}

Data list_item_data(const ListItem *item)
{
    return item->field;
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
    ListItem* ins = new ListItem;
    ins->field = data;
    if (list->first) {
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

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem* ins = new ListItem;
    ins->field = data;

    if (item->next != nullptr) {
        ins->next = item->next;
    }
    item->next = ins;
    return ins;
}

ListItem *list_erase(List *list, ListItem *item)
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
                list->last = list->last->prev;

            }
            if (item == list->first)
            {
                list->first = list->first->next;
            }
            (item->next)->prev = item->prev;
            (item->prev)->next = item->next;
            return item;
            delete item;
        }
    }
  
}

ListItem *list_erase_next(List *list, ListItem *item)
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
