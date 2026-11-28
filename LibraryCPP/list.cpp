#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem* head;
};

List *list_create()
{
    List *list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List *list)
{
    if (list == nullptr) return;

    ListItem* current = list->head;
    while (current != nullptr)
    {
        ListItem* next_item = current->next;
        delete current;
        current = next_item;
    }

    delete list;
}

ListItem *list_first(List *list)
{
    if (list == nullptr) return nullptr;

    return list->head;
}

ListItem *list_last(List *list)
{
    if (list == nullptr || list->head == nullptr) return nullptr;

    ListItem* current = list->head;
    while (current->next != nullptr) current = current->next;

    return current;
}

Data list_item_data(const ListItem *item)
{
    if (item == nullptr) return 0;

    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (item == nullptr) return nullptr;

    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (item == nullptr)
    {
        return nullptr;
    }

    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    if (list == nullptr) return nullptr;
    
    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = list->head;
    list->head = new_item;

    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (list == nullptr) return nullptr;

    if (item == nullptr) return list_insert(list, data);

    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->next = item->next;
    item->next = new_item;

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list == nullptr || list->head == nullptr) return nullptr;

    ListItem* to_delete = list->head;
    ListItem* next_item = to_delete->next;

    list->head = next_item;
    delete to_delete;

    return next_item;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list == nullptr) return nullptr;

    if (item == nullptr) return list_erase_first(list);

    if (item->next == nullptr) return nullptr;

    ListItem* to_delete = item->next;
    ListItem* next_item = to_delete->next;

    item->next = next_item;
    delete to_delete;

    return next_item;
}
