#include "list.h"

struct ListItem {
    Data data;
    ListItem* next;
    bool is_dummy;
};

struct List {
    ListItem dummy;
    ListItem* last;
};

List* list_create() {
    List* list = new List;
    list->dummy = {0, &list->dummy, true};
    list->last = &list->dummy;
    return list;
}

void list_delete(List* list) {
    if (!list) return;
    while (list_first(list)) list_erase_first(list);
    delete list;
}

ListItem* list_first(List* list) {
    return list->dummy.next == &list->dummy ? nullptr : list->dummy.next;
}

ListItem* list_last(List* list) {
    return list->last == &list->dummy ? nullptr : list->last;
}

Data list_item_data(const ListItem* item) {
    return item->data;
}

ListItem* list_item_next(ListItem* item) {
    return !item || item->next->is_dummy ? nullptr : item->next;
}

ListItem* list_insert(List* list, Data data) {
    return list_insert_after(list, nullptr, data);
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!item) item = &list->dummy;
    ListItem* added = new ListItem{data, item->next, false};
    item->next = added;
    if (list->last == item) list->last = added;
    return added;
}

ListItem* list_erase_first(List* list) {
    return list_erase_next(list, nullptr);
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (!item) item = &list->dummy;
    ListItem* removed = item->next;
    if (removed == &list->dummy) return nullptr;
    item->next = removed->next;
    if (list->last == removed) list->last = item;
    delete removed;
    return list_item_next(item);
}
