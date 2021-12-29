#include <cstddef>
#include <string>
#include "list.h"
#include <iostream>

using namespace std;
struct ListItem
{
    Data value;
    ListItem* next = NULL, * prev = NULL;
};

struct List
{
    ListItem* head;
};

List* list_create()
{
    List* result = new List;
    result->head = NULL;
    return result;
}

void list_delete(List* list)
{
    ListItem* elem = list->head;
    while (list->head != NULL)
    {
        list->head = list->head->next;
        delete elem;
        elem = list->head;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list->head;
}

Data list_item_data(const ListItem* item)
{
    return item->value;
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
    ListItem* elem = new ListItem;
    elem->value = data;
    if (list->head != NULL)
    {
        list->head->prev = elem;
        elem->next = list->head;
    }
    list->head = elem;
    return elem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* elem = new ListItem;
    elem->value = data;
    ListItem* next_elem = item->next;
    item->next = elem;
    elem->prev = item;
    elem->next = next_elem;
    if (next_elem != NULL)
    {
        next_elem->prev = elem;
    }
    return elem;
}

ListItem* list_erase(List* list, ListItem* item)
{
    ListItem* elem = item;
    if (elem == list->head)
    {
        list->head = list->head->next;
    }
    else
    {
        elem->prev->next = elem->next;
    }
    if (elem->next != NULL)
    {
        elem->next->prev = elem->prev;
    }
    ListItem* next_elem = elem->next;
    delete elem;
    return next_elem;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    ListItem* del_elem = item->next;
    return list_erase(list, del_elem);
}