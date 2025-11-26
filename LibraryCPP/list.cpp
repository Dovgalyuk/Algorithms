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
    if (!list) {
        return;
    }

    ListItem* current = list->head;
    while (current != nullptr) {
        ListItem* next = current->next;
        delete current;
        current = next;
        }
    // TODO: free items
    delete list;
}

ListItem *list_first(List *list)
{
    if (list == nullptr) {
        return nullptr;
    }
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    if (item == nullptr) {
        return 0;
    }
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if(item == nullptr) {
        return nullptr;
    }
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (item == nullptr) {
        return nullptr;
    }
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    if (list == nullptr) {
        return nullptr;
    }

    ListItem* item = new ListItem;
    item->data = data;
    item->prev = nullptr;
    item->next = list->head;
    if (list->head != nullptr) {
        list->head->prev = item;
    }
    list->head = item;

    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (list == nullptr) {
        return nullptr;
    }

    if (item == nullptr) {
        return list_insert(list, data);
    }

    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->prev = item;
    new_item->next = item->next;

    if (item->next != nullptr) {
        item->next->prev = new_item;
    }

    item->next = new_item;

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list == nullptr || !list->head) {
        return nullptr;
    }

    ListItem* first = list->head;
    ListItem* next = first->next;

    if (next != nullptr) {
        next->prev = nullptr;
    }

    delete first;
    list->head = next;
    return next;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list == nullptr || item == nullptr) {
        return nullptr;
    }

    ListItem* to_delete = item->next;
    if (to_delete == nullptr) {
        return nullptr;
    }

    item->next = to_delete->next;
    if (to_delete->next != nullptr) {
        to_delete->next->prev = item;
    }
    delete to_delete;
    return item->next;
}
