#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
};

struct List
{
    ListItem *head;
};

List *list_create()
{
    List *list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List *list)
{
    ListItem *current = list->head;
    while (current != nullptr) {
        ListItem *next = current->next;
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


ListItem *list_insert(List *list, Data data)
{
    ListItem *item_insert = new ListItem;
    item_insert->data = data;
    item_insert->next = list->head;
    list->head = item_insert;
    return item_insert;
}

ListItem *list_insert_after(ListItem *item, Data data)
{
    if (item == nullptr) return nullptr;
    ListItem *insert_after = new ListItem;
    insert_after->data = data;
    insert_after->next = item->next;

    item->next = insert_after;


    return insert_after;
}


ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr) return nullptr;

    ListItem *item_delete = list->head;
    list->head = item_delete->next;

    delete item_delete;
    return list->head;
}


ListItem *list_erase_next(ListItem *item)
{
    if (item == nullptr || item->next == nullptr) return nullptr;

    ListItem *item_delete = item->next;
    item->next = item_delete->next;

    delete item_delete;
    return item->next;
}
