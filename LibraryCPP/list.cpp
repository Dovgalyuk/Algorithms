#include <cstddef>
#include "list.h"

List* list_create()
{
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List* list)
{
    if (!list) return;

    ListItem* current = list->head;
    if (current) {
        ListItem* start = current;
        do {
            ListItem* next = current->next;
            delete current;
            current = next;
        } while (current && current != start);
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list ? list->head : nullptr;
}

Data list_item_data(const ListItem* item)
{
    return item ? item->data : (Data)0;
}

ListItem* list_item_next(ListItem* item)
{
    return item ? item->next : nullptr;
}

ListItem* list_item_prev(ListItem* item)
{
    return item ? item->prev : nullptr;
}

ListItem* list_insert(List* list, Data data)
{
    if (!list) return nullptr;

    ListItem* new_item = new ListItem;
    new_item->data = data;

    if (!list->head) {
        
        new_item->next = new_item;
        new_item->prev = new_item;
        list->head = new_item;
    }
    else {
        
        ListItem* first = list->head;
        ListItem* last = first->prev;

        new_item->next = first;
        new_item->prev = last;
        first->prev = new_item;
        last->next = new_item;

        list->head = new_item;
    }

    return new_item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    if (!list) return nullptr;

    if (!item) {
        return list_insert(list, data);
    }

    ListItem* new_item = new ListItem;
    new_item->data = data;

    new_item->next = item->next;
    new_item->prev = item;
    item->next->prev = new_item;
    item->next = new_item;

    return new_item;
}

ListItem* list_erase_first(List* list)
{
    if (!list || !list->head) return nullptr;

    ListItem* first = list->head;

    if (first->next == first) {
       
        delete first;
        list->head = nullptr;
        return nullptr;
    }
    else {
        ListItem* new_first = first->next;
        ListItem* last = first->prev;

        new_first->prev = last;
        last->next = new_first;

        delete first;
        list->head = new_first;
        return new_first;
    }
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (!list || !list->head) return nullptr;

    if (!item) {
        return list_erase_first(list);
    }

    if (item->next == list->head) {
        
        return item->next;
    }

    ListItem* to_delete = item->next;
    if (to_delete == item) {
       
        delete to_delete;
        list->head = nullptr;
        return nullptr;
    }

    item->next = to_delete->next;
    to_delete->next->prev = item;

    delete to_delete;
    return item->next;
}