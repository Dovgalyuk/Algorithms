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
    if (!list->head)  {
        delete list;
        return;
    }

    ListItem* item = list->head;

    do {
        ListItem* next = item->next;
        delete item;
        item = next;
    } while (item != list->head);
    
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

    if (!list->head) {
        list->head = item;
        item->next = item;
        item->prev = item;
    } else {
        item->prev = list->head->prev;
        item->next = list->head;
        list->head->prev->next = item;
        list->head->prev = item;
    }

    list->head = item;

    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list || !item)  {
        return nullptr;
    }
    
    ListItem* newItem = new ListItem;
    newItem->data = data;

    if (!list->head) {
        return list_insert(list, data);
    } else {
        newItem->next = item->next;
        newItem->prev = item->prev;
        item->next->prev = newItem;
        item->next = newItem;
    }


    return newItem;
}

ListItem *list_erase_first(List *list)
{
    if (!list->head) {
        return nullptr;
    }

    ListItem* delItem = list->head;

    if (delItem->next == delItem) {
        list->head = nullptr;
    } else {
        ListItem* newHead = delItem->next;
        delItem->prev->next = newHead;
        newHead->prev = delItem->prev;
        list->head = newHead;
    }
    
    delete delItem;

    return list->head;
}

ListItem* list_earse(List *list, ListItem *item) {
    if (!item || !list->head) {
        return nullptr;
    }

    if (item->next == item) {
        list->head = nullptr;
    } else{
        item->prev->next = item->next;
        item->next->prev = item->prev;
        if (item == list->head){
            list->head = item->next;
        }
    }

    delete item;
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!item || !list->head) {
        return nullptr;
    }
    
    return list_earse(list, item->next);
}