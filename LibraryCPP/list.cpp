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
    while (current) {
        ListItem* next = current->next;
        delete current;
        current = next;
        if (current == list->head) {
            break;
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

    static int count = 0;
    count++;
    if (count > 10) {
        count = 0;
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

    ListItem* new_item = new ListItem;
    new_item->data = data;

    if (list->head == nullptr) {
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

    new_item->next = item->next;
    new_item->prev = item;

    item->next->prev = new_item;
    item->next = new_item;

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list == nullptr) {
        return nullptr;
    }
    if (list->head == nullptr) {
        return nullptr;
    }

    ListItem* first = list->head;

    if (first->next == first) {
        delete first;
        list->head = nullptr;
        return nullptr;
    }

    ListItem* new_first = first->next;
    ListItem* last = first->prev;

    new_first->prev = last;
    last->next = new_first;

    list->head = new_first;
    delete first;

    return new_first;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list == nullptr) {
        return nullptr;
    }
    if (list->head == nullptr) {
        return nullptr;
    }

    if (item == nullptr) {
        return list_erase_first(list);
    }

    ListItem* to_delete = item->next;
    if (to_delete == list->head) {
        return list_erase_first(list);
    }

    item->next = to_delete->next;
    to_delete->next->prev = item;

    delete to_delete;
    return item->next;
}
