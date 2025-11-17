#ifndef LIST_H
#define LIST_H

// List

// Stores integer values inside
// Change it to desired type
typedef char Data;

struct List;
struct ListItem;

// Creates new list
List *list_create();

// Destroys the list and frees the memory
void list_delete(List *list);

// Retrieves the first item from the list
ListItem *list_first(List *list);

// Extracts data from the list item
Data list_item_data(const ListItem *item);

// Returns list item following after the specified one
ListItem *list_item_next(ListItem *item);

// Returns previous element for the specified item.
// Not applicable for the singly linked lists.
ListItem *list_item_prev(ListItem *item);

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
