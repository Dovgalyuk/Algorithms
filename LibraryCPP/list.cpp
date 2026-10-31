#include <cstddef>
#include "list.h"

struct ListItem
{
    Data data;
    ListItem* next;
    bool is_dummy;
};

struct List
{
    ListItem* head;
    ListItem* tail;
};

List *list_create()
{
    List* list = new List;
    list->head = new ListItem;
    list->head->data = 0;
    list->head->is_dummy = true;
    list->head->next = list->head;
    list->tail = list->head;
    return list;
}

void list_delete(List *list)
{
    // TODO: free items
    if (list != nullptr) {
        ListItem* current = list->head->next;
        while (current != list->head) {
            ListItem* next = current->next;
            delete current;
            current = next;
        }
        delete list->head;
        delete list;
    }
}

ListItem *list_first(List *list)
{
    if (list->head->next == list->head) {
        return nullptr;
    }
    return list->head->next;
}

ListItem *list_last(List *list)
{
    if (list->head->next == list->head) {
        return nullptr;
    }
    return list->tail;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    if (item == nullptr || item->next == nullptr || item->next->is_dummy) {
        return nullptr;
    }
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    (void)item;
    return nullptr;
}

ListItem *list_insert(List *list, Data data)
{
    return list_insert_after(list, nullptr, data);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (item == nullptr) {
        item = list->head;
    }

    ListItem* new_item = new ListItem;
    new_item->data = data;
    new_item->is_dummy = false;
    new_item->next = item->next;
    item->next = new_item;

    if (item == list->tail) {
        list->tail = new_item;
    }

    return new_item;
}

ListItem *list_erase_first(List *list)
{
    return list_erase_next(list, nullptr);
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item == nullptr) {
        item = list->head;
    }

    ListItem* to_delete = item->next;
    if (to_delete == list->head) {
        return nullptr;
    }

    item->next = to_delete->next;
    if (to_delete == list->tail) {
        list->tail = item;
    }

    delete to_delete;

    if (item->next->is_dummy) {
        return nullptr;
    }
    return item->next;
}