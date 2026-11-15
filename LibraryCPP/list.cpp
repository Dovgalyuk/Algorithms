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
    List* list = new List();
    list->head = new ListItem();
    list->head->next = list->head;
    list->head->prev = list->head;
    list->size = 0;
    return list;
}

void list_delete(List *list)
{
    if (!list) return;
    ListItem* curr = list->head->next;
    while (curr != list->head) {
        ListItem* next = curr->next;
        delete curr;
        curr = next;
    }
    delete list->head;
    delete list;
}

ListItem *list_first(List *list)
{
    if (!list || list->head->next == list->head) return NULL;
    return list->head->next;
}

ListItem *list_last(List *list)
{
    if (!list || list->head->prev == list->head) return NULL;
    return list->head->prev;
}

Data list_item_data(const ListItem *item)
{
    return item ? item->data : (Data)0;
}

ListItem *list_item_next(ListItem *item)
{
    return item ? item->next : NULL;
}

ListItem *list_item_prev(ListItem *item)
{
    return item ? item->prev : NULL;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, list->head, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list) return NULL;
    if (!item) item = list->head;

    ListItem* new_item = new ListItem();
    new_item->data = data;

    new_item->next = item->next;
    new_item->prev = item;

    item->next->prev = new_item;
    item->next = new_item;

    list->size++;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, list->head);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list || !item) return NULL;
    ListItem* to_delete = item->next;

    if (to_delete == list->head) return NULL;

    item->next = to_delete->next;
    to_delete->next->prev = item;

    ListItem* next_item = item->next;
    delete to_delete;
    list->size--;

    return next_item == list->head ? NULL : next_item;
}