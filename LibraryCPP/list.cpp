#include "list.h"

struct ListItem {
    Data data;
    ListItem* next;
    bool is_dummy;
};

struct List {
    ListItem* dummy;
};

List* list_create() {
    List* list = new List;
    list->dummy = new ListItem{0, nullptr, true};
    list->dummy->next = list->dummy;
    return list;
}

void list_delete(List* list) {
    if (!list) return;
    while (list_first(list)) list_erase_first(list);
    delete list->dummy;
    delete list;
}

ListItem* list_first(List* list) {
    return list->dummy->next == list->dummy ? nullptr : list->dummy->next;
}

ListItem* list_last(List* list) {
    ListItem* item = list_first(list);
    if (!item) return nullptr;
    while (item->next != list->dummy) item = item->next;
    return item;
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
    if (!item) item = list->dummy;
    ListItem* added = new ListItem{data, item->next, false};
    item->next = added;
    return added;
}

ListItem* list_append(List* list, Data data) {
    // Старый фиктивный узел становится последним, новый замыкает кольцо.
    ListItem* added = list->dummy;
    ListItem* dummy = new ListItem{0, added->next, true};
    added->data = data;
    added->is_dummy = false;
    added->next = dummy;
    list->dummy = dummy;
    return added;
}

ListItem* list_erase_first(List* list) {
    return list_erase_next(list, nullptr);
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (!item) item = list->dummy;
    ListItem* removed = item->next;
    if (removed == list->dummy) return nullptr;
    item->next = removed->next;
    delete removed;
    return list_item_next(item);
}
