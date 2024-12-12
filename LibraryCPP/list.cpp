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
    ListItem* tail;
    size_t size;
};

List* list_create()
{
    List* list = new List;
    list->head = nullptr;
    list->tail = nullptr;
    list->size = 0;
    return list;
}

void list_delete(List* list)
{
    ListItem* current = list->head;
    while (current != nullptr) {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}

ListItem* list_first(List* list)
{
    return list->head;
}

Data list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item->next;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* item = new ListItem;
    item->data = data;
    item->next = list->head;
    list->head = item;
    if (list->tail == nullptr) {
        list->tail = item;
    }
    list->size++;
    return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data)
{
    ListItem* newItem = new ListItem;
    newItem->data = data;
    newItem->next = item->next;
    item->next = newItem;
    if (list->tail == item) {
        list->tail = newItem;
    }
    list->size++;
    return newItem;
}

ListItem* list_erase_first(List* list)
{
    if (list->head == nullptr) {
        return nullptr;
    }
    ListItem* item = list->head;
    list->head = item->next;
    if (list->head == nullptr) {
        list->tail = nullptr;
    }
    delete item;
    list->size--;
    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (item->next == nullptr) {
        return nullptr;
    }
    ListItem* toDelete = item->next;
    item->next = toDelete->next;
    if (list->tail == toDelete) {
        list->tail = item;
    }
    delete toDelete;
    list->size--;
    return item->next;
}
