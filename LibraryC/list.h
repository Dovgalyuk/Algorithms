#ifndef LIST_H
#define LIST_H

// List
// Stores pointer to custom user data
typedef void* Data;
// Custom function to free user pointers on delete
typedef void (FFree)(void*);

typedef struct List List;
typedef struct ListItem ListItem;

#ifdef __cplusplus
extern "C" {
#endif

// Creates new list
List *list_create(FFree f);

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
ListItem *list_insert_after(List *list, ListItem *item, Data data);

// Deletes the specified list item.
// Returns pointer to the item next to the deleted one.
// Not applicable for the singly linked lists.
// Should be O(1)
ListItem *list_erase(List *list, ListItem *item);

// Deletes the list item following the specified one.
// Returns pointer to the item next to the deleted one.
// Should be O(1)
ListItem *list_erase_next(List *list, ListItem *item);

#ifdef __cplusplus
}
#endif

#endif
