#include <cstddef>
#include "list.h"

struct ListItem {
    Data dataListItem;
    ListItem* nextItem;
    ListItem(Data dataListItem, ListItem* nextItem = nullptr) {
        this->dataListItem = dataListItem;
        this->nextItem = nextItem;
    }
};

struct List {
    ListItem* firstItem;
    List() {
        firstItem = nullptr;
    }
};

List* list_create() {
    return new List;
}
List* list_null(List* list) {
    return list;
}

void list_delete(List* list) {
    delete list;
}

ListItem* list_first(List* list) {
    return list->firstItem;
}

Data list_item_data(const ListItem* item) {
    if (item != nullptr) return item->dataListItem;
    else return 0;
}

ListItem* list_item_next(ListItem* item) {
    return item->nextItem;
}

ListItem* list_insert(List* list, Data data) {
    list->firstItem = new ListItem(data, list->firstItem);
    return list->firstItem;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    ListItem* listItem = new ListItem(data);
    listItem->nextItem = item->nextItem;
    item->nextItem = listItem;
    return listItem;
}
ListItem* list_erase_first(List* list) {
    ListItem* tempPtr;
    if (list->firstItem == nullptr)
        return NULL;
    else {
        tempPtr = list->firstItem;
        list->firstItem = list->firstItem->nextItem;
        delete tempPtr;
        return list->firstItem;
    }
}

ListItem* list_erase(List* list, ListItem* item) {
    if (item == list_first(list))
        return list_erase_first(list);
    return NULL;
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (list_item_next(item)) {
        ListItem* tempPtr = item->nextItem;
        item->nextItem = nullptr;
        delete tempPtr;
        return item;
    }
    else return NULL;
}
