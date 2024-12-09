#include <cstddef>
#include <iostream>
#include <stdexpected>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem next;
    ListItem previous;
};

struct List
{
    ListItem* head;
};

List *list_create()
{
    List* list = new list;
    list->head = nullptr;
    return list;
}

void list_clear(List *list){
    while(!list_empty(list)){
        list_erase_first(list);
    }
}

void list_delete(List *list)
{
    if(list){
        list_clear(list);
        delete list;
    }
}

ListItem *list_first(List *list)
{
    return NULL;
}

Data list_item_data(const ListItem *item)
{
    return (Data)0;
}

ListItem *list_item_next(ListItem *item)
{
    return NULL;
}

ListItem *list_item_prev(ListItem *item)
{
    return NULL;
}

ListItem *list_insert(List *list, Data data)
{
    return NULL;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    return NULL;
}

ListItem *list_erase_first(List *list)
{
    return NULL;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    return NULL;
}
