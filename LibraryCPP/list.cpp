#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
    ListItem* previous;

    ListItem(Data d) : data(d), next(nullptr), previous(nullptr) {}
};

struct List
{
    ListItem* head;
    ListItem* tail;

    List() : head(nullptr), tail(nullptr) {}
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    ListItem* current = list->head;
    while (current != nullptr) {
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
    return item->previous;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem* new_item = new ListItem(data);

    if (list->head == nullptr) {
        list->head = new_item;
        list->tail = new_item;
    }
    else {
        new_item->next = list->head;
        list->head->previous = new_item;
        list->head = new_item;
    }
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr) {
        return list_insert(list, data);
    }
    ListItem* new_item = new ListItem(data);

    new_item->next = item->next;
    new_item->previous = item;

    if (item->next != nullptr) {
        item->next->previous = new_item;
    }
    else {
        list->tail = new_item;
    }
    item->next = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == nullptr)
        return nullptr;
    ListItem* to_delete = list->head;
    list->head = to_delete->next;

    if (list->head != nullptr) {
        list->head->previous = nullptr;
    }
    else {
        list->tail = nullptr;
    }
    ListItem* result = list->head;
    delete to_delete;
    return result;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr)
        return list_erase_first(list);
    if (item->next == nullptr)
        return nullptr;

    ListItem* to_delete = item->next;
    item->next = to_delete->next;

    if (to_delete->next != nullptr)
        to_delete->next->previous = item;
    else
        list->tail = item;

    ListItem* result = item->next;
    delete to_delete;
    return result;
}
