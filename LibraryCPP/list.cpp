#include <cstddef>
#include "list.h"

struct ListItem
{
    ListItem *prev;
    Data value;
    ListItem *next;

    ListItem(Data val) : prev(nullptr), value(val), next(nullptr) {}
    ~ListItem() = default;
};

struct List
{
    ListItem *head = nullptr;
    ListItem *tail = nullptr;
    size_t size = 0;

    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List() {
        ListItem *curr = head;
        while (curr != nullptr) {
            ListItem *next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
        tail = nullptr;
        delete curr;
    };
};

List *list_create()
{
    return new List;
}

void list_delete(List *list)
{
    delete list;
}

ListItem *list_first(List *list)
{
    return list->head;
}

ListItem *list_last(List *list)
{
    return list->tail;
}

Data list_item_data(const ListItem *item)
{
    return item->value;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *item = new ListItem(data);
    if (list->size == 0) {
        list->head = item;
        list->tail = item;
    } else {
        item->prev = list->tail;
        list->tail->next = item;
        list->tail = item;
    }
    list->size++;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *new_item = new ListItem(data);
    bool flaged = false;

    if (list->head == list->tail && list->head == nullptr) {
        list->head = new_item;
        list->tail = new_item;
        flaged = true;
    }

    if (!flaged) {
        new_item->next = list_item_next(item);
        new_item->prev = item;
        item->next = new_item;
        ListItem *temp = list_item_next(new_item);
        temp->prev = new_item;
    }

    list->size++;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->size == 0) {
        list->head = nullptr;
        list->tail = nullptr;
    } else if (list->size == 1) {
        ListItem *item = list->head;
        list->head = nullptr;
        list->tail = nullptr;
        delete item;
    } else {
        ListItem *item = list->head;
        list->head = list->head->next;
        list->head->prev = nullptr;
        delete item;
    }
    list->size--;
    return nullptr;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (list->size == 0) {
        list->head = nullptr;
        list->tail = nullptr;
    } else if (list->size == 1) {
        ListItem *temp = list->head;
        list->head = nullptr;
        list->tail = nullptr;
        delete temp;
    } else {
        ListItem* next = list_item_next(item);
        ListItem* temp = next;
        next = list_item_next(next);
        item->next = next;
        delete temp;
    }
    list->size--;
    return nullptr;
}
