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
};

List *list_create()
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List *list)
{
    // TODO: free items    
    while (list->head != nullptr) {
        list_erase(list, list->head);
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
    ListItem* item = new ListItem;
    item->data = data;
    item->next = list->head;
    item->prev = nullptr;
    if (list->head != nullptr) {
        list->head->prev = item;
    }
    list->head = item;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    new_item->prev = item;
    if (item->next != nullptr) {
        item->next->prev = new_item;
    }
    item->next = new_item;
    return new_item;
}

ListItem *list_erase(List *list, ListItem *item)
{
    if (list->head == nullptr) 
        return nullptr;
    if (item->prev != nullptr) {
        item->prev->next = item->next; 
    }
    else
        list->head = item->next; 
    if (item->next != nullptr) {
        item->next->prev = item->prev; 
    }
    delete item;
    return 0;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item->next != nullptr)
        return list_erase(list, item->next);
    else return item;
}
