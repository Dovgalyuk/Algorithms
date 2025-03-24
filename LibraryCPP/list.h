#ifndef LIST_H
#define LIST_H

#include <string> 

typedef std::string Data;

struct ListItem {
    Data data;
    ListItem* next;
};

struct List {
    ListItem* head;
};

List* list_create();
void list_delete(List* list);
ListItem* list_first(List* list);
Data list_item_data(const ListItem* item);
ListItem* list_item_next(ListItem* item);


ListItem* list_insert(List* list, Data data);

ListItem* list_insert_after(List* list, ListItem* item, Data data);
ListItem* list_erase_first(List* list);
ListItem* list_erase_next(ListItem* item);


// Inserts new list item into the beginning
ListItem *list_insert(List *list, Data data);

// Inserts new list item after the specified item
// Inserts first element if item is null
ListItem *list_insert_after(List *list, ListItem *item, Data data);

// Deletes the first list item.
// Returns pointer to the item next to the deleted one.
ListItem *list_erase_first(List *list);

// Deletes the list item following the specified one.
// Deletes the first element when item is null.
// Returns pointer to the item next to the deleted one.
// Should be O(1)
ListItem *list_erase_next(List *list, ListItem *item);

#endif

