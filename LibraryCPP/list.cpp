#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next = NULL;
    ListItem* prev = NULL;

    ListItem(Data data) : data(data) {};
};

struct List
{
    ListItem* first = NULL;
};

List* list_create()
{
    return new List;
}

void list_delete(List* list)
{
    // TODO: free items
    ListItem* item = list->first;
    while (item != list->first->prev) {
        ListItem* delet = item;
        item = list->first->next;
        delete delet;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list->first;
}

ListItem* list_last(List* list)
{
    return list->first->prev;
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
    ListItem* item = new ListItem(data);
    item->next = list->first;
    if (list->first) {
        item->prev = list->first->prev;
        list->first->prev = item;
    }
    else {
        item->next = item;
    }
    list->first = item;
    if (item->prev) {
        item->prev->next = item;
    }
    else {
        item->prev = list->first;
    }
    return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* new_item = new ListItem(data);
    new_item->next = item->next;
    new_item->next->prev = new_item;
    item->next = new_item;
    new_item->prev = item;
    return new_item;
}

ListItem* list_erase(List* list, ListItem* item)
{
    if (list->first == item && list->first->next == list->first) {
        delete item;
        list->first = NULL;
        return NULL;
    }
    else if (list->first == item) {
        list->first = item->next;
    }
    item->next->prev = item->prev;
    item->prev->next = item->next;
    auto* next = item->next;
    delete item;
    return next;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    return list_erase(list, item->next);
}