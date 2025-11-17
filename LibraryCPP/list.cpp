#include <cstddef>
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
    size_t size;
};

List *list_create()
{
    List* list = new List;
    list->head = nullptr;
    list->size = 0;
    return list;
}

void list_delete(List *list)
{
    if (!list) return;
    while (list->size > 0) 
    {
        list_erase_first(list);
    }
    delete list;
}

ListItem *list_first(List *list)
{
    if (!list || list->size == 0) return nullptr;
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    if (!item) return '\0';
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (!item) return nullptr;
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (!item) return nullptr;
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, nullptr, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list) return nullptr;
    
    ListItem* new_item = new ListItem;
    new_item->data = data;
    
    if (list->size == 0) 
    {
        new_item->next = new_item;
        new_item->prev = new_item;
        list->head = new_item;
    } 
    else if (!item) 
    {
        ListItem* tail = list->head->prev;
        new_item->next = list->head;
        new_item->prev = tail;
        list->head->prev = new_item;
        tail->next = new_item;
        list->head = new_item;
    } 
    else 
    {
        new_item->next = item->next;
        new_item->prev = item;
        item->next->prev = new_item;
        item->next = new_item;
    }
    list->size++;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, nullptr);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list || list->size == 0) return nullptr;
    ListItem* to_delete = nullptr;
    ListItem* result = nullptr;
    
    if (!item) 
    {
        to_delete = list->head;
        
        if (list->size == 1) 
        {
            list->head = nullptr;
            result = nullptr;
        } 
        else 
        {
            list->head = to_delete->next;
            result = list->head;
            to_delete->prev->next = list->head;
            list->head->prev = to_delete->prev;
        }
    } 
    else 
    {
        to_delete = item->next;
        if (to_delete == list->head) 
        {
            list->head = to_delete->next;
        }
        result = to_delete->next;
        item->next = to_delete->next;
        to_delete->next->prev = item;
    }
    delete to_delete;
    list->size--;
    if (list->size == 0) 
    {
        list->head = nullptr;
    }
    
    return result;
}