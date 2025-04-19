#include "list.h"
#include <cstdlib>

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

List* list_create() 
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List* list) 
{
    while (list->head) 
    {
        ListItem* tmp = list->head;
        list->head = list->head->next;
        delete tmp;
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
    ListItem* item = new ListItem{ data, list->head, nullptr };
    if (list->head) {
        list->head->prev = item;
    }
    list->head = item;
    return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) 
{
    if (item == nullptr) 
    {
        return list_insert(list, data);
    }
    ListItem* new_item = new ListItem{ data, item->next, item };
    if (item->next) 
    {
        item->next->prev = new_item;
    }
    item->next = new_item;
    return new_item;
}

ListItem* list_erase_first(List* list) 
{
    if (!list->head) return nullptr;
    ListItem* next = list->head->next;
    if (next) 
    {
        next->prev = nullptr;
    }
    delete list->head;
    list->head = next;
    return next;
}

ListItem* list_erase_next(List* list, ListItem* item) 
{
    if (item == nullptr) 
    {
        return list_erase_first(list);
    }
    ListItem* to_delete = item->next;
    if (!to_delete) return nullptr;
    item->next = to_delete->next;
    if (to_delete->next) 
    {
        to_delete->next->prev = item;
    }
    delete to_delete;
    return item->next;
}
