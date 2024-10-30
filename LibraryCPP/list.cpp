#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem *prev;
    ListItem *next;
};

struct List
{
    ListItem *head;
};

List *list_create()
{
    List *list = new List;
    list->head = nullptr;

    return list;
}

void list_delete(List *list)
{
    ListItem *curr = list->head;
    while(curr != nullptr)
    {
        ListItem *next = curr->next;
        delete curr;
        curr = next;
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
    ListItem *newItem = new ListItem;
    newItem->data = data;
    newItem->next = list->head;
    newItem->prev = nullptr;

    if(list->head != nullptr)
        list->head->prev = newItem;

    list->head = newItem;

    return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    newItem->prev = item;

    if(item->next != nullptr)
        item->next->prev = newItem;

    item->next = newItem;

    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if(list->head == nullptr)
        return nullptr;

    ListItem *tempItem = list->head;

    list->head = list->head->next; 
    if(list->head != nullptr)
        list->head->prev = nullptr;
    
    delete tempItem;
    return list->head ;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if(item->next == nullptr)
        return nullptr;

    ListItem *tempItem = item->next;

    item->next = tempItem->next;
    if(tempItem->next != nullptr)
        tempItem->next->prev = item;

    delete tempItem;
    return item->next;
}
