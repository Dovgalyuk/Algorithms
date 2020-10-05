#ifndef LIST_H
#define LIST_H

// List
// Stores integer values inside
typedef int Data;

struct ListItem
{
	Data data;
	ListItem* next;
};

struct List
{
	ListItem* first;
};

// Creates new list
List* list_create();

// Retrieves the first item from the list
ListItem* list_first(List* list);

// Extracts data from the list item
Data list_get(const ListItem* item);

// Returns list item following after the specified one
ListItem* list_item_next(ListItem* item);

// Inserts new list item into the beginning
void list_insert(List* list, Data data);

// Inserts new list item after the specified item
void list_insert_after(List* list, ListItem* item, Data data);

// Deletes the list item following the specified one
// Should be O(1)
void list_erase_next(List* list, ListItem* item);

void list_erase_first(List* list);

// Destroys the list and frees the memory
void list_delete(List* list);

#endif