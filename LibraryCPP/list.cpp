#include <cstddef>
#include "list.h"

struct ListItem {
    Data data;
    ListItem* prev;
    ListItem* next;
};

struct List {
    ListItem* head;
};

List* list_create() {
    List* list = new List;
    list->head = nullptr;
    return list;
}

void list_delete(List* list) {
    if (!list)
        return;

    ListItem* it = list->head;
    while (it) {
        ListItem* nxt = it->next;
        delete it;
        it = nxt;
    }

    delete list;
}

ListItem* list_first(List* list) {
    return list ? list->head : nullptr;
}

Data list_item_data(const ListItem* item) {
    return item ? item->data : (Data)0;
}

ListItem* list_item_next(ListItem* item) {
    return item ? item->next : nullptr;
}

ListItem* list_item_prev(ListItem* item) {
    return item ? item->prev : nullptr;
}

ListItem* list_insert(List* list, Data data) {
    ListItem* node = new ListItem{ data, nullptr, nullptr };
    node->next = list->head;

    if (list->head)
        list->head->prev = node;

    list->head = node;
    return node;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!item)
        return list_insert(list, data);

    ListItem* node = new ListItem{ data, item, item->next };

    if (item->next)
        item->next->prev = node;

    item->next = node;
    return node;
}

ListItem* list_erase_first(List* list) {
    if (!list || !list->head)
        return nullptr;

    ListItem* rem = list->head;
    ListItem* newHead = rem->next;

    if (newHead)
        newHead->prev = nullptr;

    delete rem;
    list->head = newHead;
    return newHead;
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (!list)
        return nullptr;
    if (!item)
        return list_erase_first(list);

    ListItem* rem = item->next;
    if (!rem)
        return nullptr;

    ListItem* after = rem->next;
    item->next = after;

    if (after)
        after->prev = item;

    delete rem;
    return after;
}