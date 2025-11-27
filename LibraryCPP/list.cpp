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
    if (list->head != nullptr) {
        ListItem* last = list->head->prev;
        last->next = nullptr;

        ListItem* current = list->head;
        while (current != nullptr) {
            ListItem* next = current->next;
            delete current;
            current = next;
        }
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

    if (list->head == nullptr) {
        item->next = item;
        item->prev = item;
        list->head = item;
    }
    else {
        ListItem* first = list->head;
        ListItem* last = first->prev;

        item->next = first;
        item->prev = last;

        first->prev = item;
        last->next = item;

        list->head = item;
    }
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

    ListItem* next = item->next;
    new_item->next = next;
    new_item->prev = item;

    item->next = new_item;
    next->prev = new_item;

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list == nullptr || !list->head) {
        return nullptr;
    }

    ListItem* next = list->head->next;
    ListItem* prev = list->head->prev;
    ListItem* to_delete = list->head;

    if (next == to_delete) {
        list->head = nullptr;
    }
    else {
        list->head = next;
        next->prev = prev;
        prev->next = next;
    }

    delete to_delete;
    return list->head;

}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list == nullptr) {
        return nullptr;
    }

    if (item == nullptr) {
        return list_erase_first(list);
    }

    ListItem* to_delete = item->next;
    if (to_delete == nullptr || to_delete == item) {
        return nullptr;
    }

    ListItem* next = to_delete->next;

    item->next = next;
    next->prev = item;

    if (to_delete == list->head) {
        list->head = next;
    }

    delete to_delete;
    return next;
}
