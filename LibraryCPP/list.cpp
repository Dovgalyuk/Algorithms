#include <cstddef> 
#include <iostream> 
#include "list.h"

typedef int Data;  

struct ListItem {
    Data data;
    ListItem *next;
    ListItem *prev;
};

struct List {
    ListItem *head;
    ListItem *tail; 
    size_t size;
};

List *list_create() {
    List *list = new List;
    if (list) {
        list->head = nullptr;
        list->tail = nullptr;
        list->size = 0;
    }
    return list;
}

void list_delete(List *list) {
    if (list) {
        ListItem *current = list->head;
        while (current) {
            ListItem *next = current->next;
            delete current;
            current = next;
        }
        list->head = nullptr;
        list->tail = nullptr;
        list->size = 0;
        delete list;
    }
}


ListItem *list_first(List *list) {
    if (list) {
        return list->head;
    }
    return nullptr;
}

Data list_item_data(const ListItem *item) {
    if (item) {
        return item->data;
    }
    return (Data)0; // Or throw an exception, or return a sentinel value
}

ListItem *list_item_next(ListItem *item) {
    if (item) {
        return item->next;
    }
    return nullptr;
}

ListItem *list_item_prev(ListItem *item) {
    if (item) {
        return item->prev;
    }
    return nullptr;
}

ListItem *list_insert(List *list, Data data) {
    if (!list) {
        return nullptr;
    }

    ListItem *newItem = new ListItem;
    if (!newItem) {
        std::cerr << "Memory allocation failed in list_insert!" << std::endl;
        return nullptr;
    }

    newItem->data = data;
    newItem->next = list->head;
    newItem->prev = nullptr; 
    if (list->head) {
        list->head->prev = newItem;
    }
    list->head = newItem; 
    if (!list->tail) {
        list->tail = newItem;  
    }
    list->size++;

    return newItem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data) {
    if (!list || !item) {
        return nullptr;
    }

    ListItem *newItem = new ListItem;
    if (!newItem) {
        std::cerr << "Memory allocation failed in list_insert_after!" << std::endl;
        return nullptr;
    }

    newItem->data = data;
    newItem->next = item->next;
    newItem->prev = item;

    if (item->next) {
        item->next->prev = newItem;
    } else {
        list->tail = newItem; 
    }
    item->next = newItem;
    list->size++;
    return newItem;
}

void list_erase_first(List *list) {
    if (!list || !list->head) {
        return;
    }

    ListItem *firstItem = list->head;
    list->head = firstItem->next;
    
    if (list->head) {
        list->head->prev = nullptr;
    } else {
        list->tail = nullptr;
    }

    list->size--;
    delete firstItem; 
}


void list_erase_next(List *list, ListItem *item) {
    if (!list || !item || !item->next) {
        return;
    }

    ListItem *itemToRemove = item->next;
    item->next = itemToRemove->next;

    if (itemToRemove->next) {
        itemToRemove->next->prev = item;
    } else {
        list->tail = item;
    }

    list->size--;
    delete itemToRemove; 
}
