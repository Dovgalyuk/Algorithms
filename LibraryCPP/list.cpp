#include "list.h"

struct ListItem {
    Data data;
    ListItem* next;
};

struct List {
    ListItem* head;
};

List* list_create() {
    List* lst = new List;
    lst->head = nullptr;
    return lst;
}

void list_delete(List* list) {
    if (!list) return;
    ListItem* cur = list->head;
    while (cur) {
        ListItem* nxt = cur->next;
        delete cur;
        cur = nxt;
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

ListItem* list_item_prev(ListItem* /*item*/) {
    return nullptr;
}

ListItem* list_insert(List* list, Data data) {
    if (!list) return nullptr;
    ListItem* node = new ListItem{data, list->head};
    list->head = node;
    return node;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!list) return nullptr;
    if (item == nullptr) return list_insert(list, data);
    ListItem* node = new ListItem{data, item->next};
    item->next = node;
    return node;
}

ListItem* list_erase_first(List* list) {
    if (!list || !list->head) return nullptr;
    ListItem* old = list->head;
    list->head = old->next;
    delete old;
    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (!list) return nullptr;
    if (item == nullptr) return list_erase_first(list);
    if (!item->next) return nullptr;
    ListItem* victim = item->next;
    item->next = victim->next;
    ListItem* next_after = item->next;
    delete victim;
    return next_after;
}
