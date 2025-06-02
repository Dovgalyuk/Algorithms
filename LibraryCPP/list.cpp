#include "list.h"
#include <stdexcept>
#include <iostream>

struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;

    ListItem(Data d) : data(d), next(nullptr), prev(nullptr) {}
};

struct List {
    ListItem* head;
    size_t size;

    List() : head(nullptr), size(0) {}
    
    ~List() {
        clear();
    }
    
    void clear() {
        while (head) {
            ListItem* toDelete = head;
            head = (head->next == head || !head->next) ? nullptr : head->next;
            delete toDelete;
        }
        size = 0;
    }
};

List* list_create() {
    try {
        return new List();
    } catch (const std::bad_alloc&) {
        std::cerr << "Memory allocation failed in list_create()" << std::endl;
        return nullptr;
    }
}

void list_delete(List* list) {
    if (list) {
        list->clear();
        delete list;
    }
}

ListItem* list_first(List* list) {
    return list ? list->head : nullptr;
}

Data list_item_data(const ListItem* item) {
    if (!item) throw std::invalid_argument("Null item in list_item_data");
    return item->data;
}

ListItem* list_item_next(ListItem* item) {
    return item ? item->next : nullptr;
}

ListItem* list_item_prev(ListItem* item) {
    return item ? item->prev : nullptr;
}

ListItem* list_insert(List* list, Data data) {
    return list_insert_after(list, nullptr, data);
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!list) throw std::invalid_argument("Null list in list_insert_after");

    ListItem* newItem;
    try {
        newItem = new ListItem(data);
    } catch (const std::bad_alloc&) {
        throw std::runtime_error("Memory allocation failed in list_insert_after");
    }

    if (!list->head) {
        newItem->next = newItem;
        newItem->prev = newItem;
        list->head = newItem;
    } else if (!item) {
        newItem->next = list->head;
        newItem->prev = list->head->prev;
        list->head->prev->next = newItem;
        list->head->prev = newItem;
        list->head = newItem;
    } else {
        newItem->next = item->next;
        newItem->prev = item;
        item->next->prev = newItem;
        item->next = newItem;
    }

    list->size++;
    return newItem;
}

ListItem* list_erase_first(List* list) {
    return list_erase_next(list, nullptr);
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (!list || !list->head) return nullptr;

    ListItem* toDelete = item ? item->next : list->head;
    if (!toDelete) return nullptr;

    if (toDelete->next == toDelete) {
        list->head = nullptr;
    } else {
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        
        if (toDelete == list->head) {
            list->head = toDelete->next;
        }
    }

    ListItem* nextItem = toDelete->next;
    delete toDelete;
    list->size--;

    return (nextItem == toDelete) ? nullptr : nextItem;
}