#include <cstddef>
#include "list.h"


struct ListItem {

};

struct List {

};


List* list_create() {
    return new List;
}

void list_delete(List* list) {
    delete list;
}

ListItem* list_first(List* list) {
    (void)list;
    return nullptr;
}

Data list_item_data(const ListItem* item) {
    (void)item;
    return 0;
}

ListItem* list_item_next(ListItem* item) {
    (void)item;
    return nullptr;
}

ListItem* list_item_prev(ListItem* item) {
    (void)item;
    return nullptr;
}

ListItem* list_insert(List* list, Data data) {
    (void)list;
    (void)data;
    return nullptr;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    (void)list;
    (void)item;
    (void)data;
    return nullptr;
}

ListItem* list_erase_first(List* list) {
    (void)list;
    return nullptr;
}

ListItem* list_erase_next(List* list, ListItem* item) {
    (void)list;
    (void)item;
    return nullptr;
}
