#ifndef LIST_H
#define LIST_H

typedef char Data;

struct ListItem;
struct List;

// Creates an empty list
List *list_create();

// Deletes the list
void list_delete(List *list);

// Inserts data at the beginning
ListItem *list_insert(List *list, Data data); // Изменено на ListItem*

// Inserts data after a given item
ListItem *list_insert_after(List *list, ListItem *item, Data data); // Изменено на ListItem*

// Erases the first item
ListItem *list_erase_first(List *list); // Изменено на ListItem*

// Returns the first item
ListItem *list_first(const List *list);

// Returns the data of the item
Data list_item_data(const ListItem *item);

// Returns the next item
ListItem *list_item_next(const ListItem *item);

#endif
