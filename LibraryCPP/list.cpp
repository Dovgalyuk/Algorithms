#include <cstddef>
#include "list.h"

struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;
    bool is_dummy;
};

struct List {
    ListItem* dummy;   // фиктивный элемент
};

List* list_create() {
    List* list = new List;
    list->dummy = new ListItem;
    list->dummy->is_dummy = true;
    list->dummy->next = list->dummy;
    list->dummy->prev = list->dummy;
    return list;
}

void list_delete(List* list) {
    if (!list) return;
    ListItem* cur = list->dummy->next;
    while (cur != list->dummy) {
        ListItem* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    delete list->dummy;
    delete list;
}

ListItem* list_first(List* list) {
    if (!list || list->dummy->next == list->dummy) return nullptr;
    return list->dummy->next;
}

ListItem* list_last(List* list) {
    if (!list || list->dummy->prev == list->dummy) return nullptr;
    return list->dummy->prev;
}

Data list_item_data(const ListItem* item) {
    return item->data;
}

ListItem* list_item_next(ListItem* item) {
    if (item->next->is_dummy) return nullptr;
    return item->next;
}

ListItem* list_item_prev(ListItem* item) {
    if (item->prev->is_dummy) return nullptr;
    return item->prev;
}

ListItem* list_insert(List* list, Data data) {
    return list_insert_after(list, list->dummy, data);
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!item) item = list->dummy;
    ListItem* ni = new ListItem;
    ni->data = data;
    ni->is_dummy = false;
    ni->prev = item;
    ni->next = item->next;
    item->next->prev = ni;
    item->next = ni;
    return ni;
}

ListItem* list_erase_first(List* list) {
    if (list->dummy->next == list->dummy) return nullptr;
    ListItem* target = list->dummy->next;
    ListItem* nxt = target->next;
    target->prev->next = target->next;
    target->next->prev = target->prev;
    delete target;
    return (nxt == list->dummy) ? nullptr : nxt;
}

ListItem* list_erase_next(List* list, ListItem* item) {
    ListItem* target = item ? item->next : list->dummy->next;
    if (target == list->dummy) return nullptr;
    ListItem* nxt = target->next;
    target->prev->next = target->next;
    target->next->prev = target->prev;
    delete target;
    return (nxt == list->dummy) ? nullptr : nxt;
}