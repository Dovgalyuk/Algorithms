#include "list.h"
#include <cstddef>

struct List;

struct ListItem {
    Data data;
    ListItem *prev;
    ListItem *next;
    List *parent;
};

struct List {
    ListItem *sentinel;
};

List *list_create() {
    List *list = new List;
    list->sentinel = new ListItem;
    list->sentinel->prev = list->sentinel;
    list->sentinel->next = list->sentinel;
    list->sentinel->parent = list;
    return list;
}

void list_delete(List *list) {
    ListItem *cur = list->sentinel->next;
    while (cur != list->sentinel) {
        ListItem *tmp = cur->next;
        delete cur;
        cur = tmp;
    }

    delete list->sentinel;
    delete list;
}

ListItem *list_first(List *list) {
    ListItem *first = list->sentinel->next;
    return (first == list->sentinel ? nullptr : first);
}

Data list_item_data(const ListItem *item) {
    return item->data;
}

ListItem *list_item_next(const ListItem *item) {
    ListItem *n = item->next;
    return (n->parent == item->parent && n != item->parent->sentinel ? n : nullptr);
}

ListItem *list_item_prev(const ListItem *item) {
    ListItem *p = item->prev;
    return (p->parent == item->parent && p != item->parent->sentinel ? p : nullptr);
}

ListItem *list_insert_after(List *list, ListItem *item, Data data) {
    ListItem *pos = item ? item : list->sentinel;
    ListItem *node = new ListItem{ data, pos, pos->next, list };
    pos->next->prev = node;
    pos->next = node;
    return node;
}

ListItem *list_insert(List *list, Data data) {
    return list_insert_after(list, nullptr, data);
}

ListItem *list_erase_first(List *list) {
    if (list->sentinel->next == list->sentinel) return nullptr;
    return list_erase_next(list, nullptr);
}

ListItem *list_erase_next(List *list, ListItem *item) {
    ListItem *pos = item ? item : list->sentinel;
    ListItem *to_del = pos->next;
    if (to_del == list->sentinel) return nullptr;
    ListItem *next = to_del->next;
    pos->next = next;
    next->prev = pos;
    delete to_del;
    return (next == list->sentinel ? nullptr : next);
}