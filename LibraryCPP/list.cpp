#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* prev;
    ListItem* next;
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
    ListItem* current = list->head;
    while (current) {
        ListItem* next = current->next;
        delete current;
        current = next;
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

ListItem* list_insert(List* list, Data data)
{
    ListItem* item = new ListItem{ data, nullptr, list->head };
    if (list->head) {
        list->head->prev = item;
    }
    list->head = item;
    return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* new_item = new ListItem{ data, item, item->next };
    if (item->next) {
        item->next->prev = new_item;
    }
    item->next = new_item;
    return new_item;
}

ListItem* list_erase_first(List* list)
{
    if (!list->head) return nullptr;
    ListItem* item = list->head;
    list->head = item->next;
    if (list->head) {
        list->head->prev = nullptr;
    }
    delete item;
    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (!item->next) return nullptr;
    ListItem* to_delete = item->next;
    item->next = to_delete->next;
    if (to_delete->next) {
        to_delete->next->prev = item;
    }
    delete to_delete;
    return item->next;
}