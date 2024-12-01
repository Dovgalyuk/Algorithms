#include <cstddef>
#include "list.h"

struct ListItem {
    Data data;
    ListItem *next;
};

struct List {
    ListItem *first;
    ListItem *last;
};

List *list_create(){
    List *list = new List;
    list->first = nullptr;
    list->last = nullptr;
    return list;
}

// Destroys the list and frees the memory
void list_delete(List *list){
    ListItem *curItem = list->first;
    while (curItem != nullptr){
        ListItem *nextItem = curItem->next;
        delete curItem;
        curItem = nextItem;
    }
    delete list;
}

// Retrieves the first item from the list
ListItem *list_first(List *list){
    return list->first;
}

// Extracts data from the list item
Data list_item_data(const ListItem *item){
    if (item != nullptr){
        return item->data;
    } else {
        return (Data)0;
    }
}

// Returns list item following after the specified one
ListItem *list_item_next(ListItem *item){
    return item->next;
}

// Inserts new list item into the beginning
ListItem *list_insert(List *list, Data data){
    ListItem *newItem = new ListItem{data, nullptr};

    if (list->first == nullptr){
        list->first = newItem;
        list->last = newItem;
    } else {
        newItem->next = list->first;
        list->first = newItem;
    }
    return newItem;
}

// Inserts new list item after the specified item
ListItem *list_insert_after(List *list, ListItem *item, Data data){
    if (item == nullptr){
        return list_insert(list, data);
    } else {
        ListItem *newItem = new ListItem{data, item->next};
        item->next = newItem;

        if (newItem->next == nullptr){
            list->last = newItem;
        }

        return newItem;
    }
}

// Deletes the first list item.
// Returns pointer to the item next to the deleted one.
ListItem *list_erase_first(List *list){
    if (list->first == nullptr){
        return nullptr;
    }

    ListItem *deleteItem = list->first;
    list->first = deleteItem->next;

    if(list->first == nullptr){
        list->last = nullptr;
    }

    delete deleteItem;
    return list->first;
}

// Deletes the list item following the specified one.
// Returns pointer to the item next to the deleted one.
// Should be O(1)
ListItem *list_erase_next(List *list, ListItem *item){
    if (item == nullptr || item->next == nullptr){
        return nullptr;
    }

    ListItem *deleteItem = item->next;
    item->next = deleteItem->next;

    if(item->next == nullptr){
        list->last = item;
    }

    delete deleteItem;
    return item->next;
}