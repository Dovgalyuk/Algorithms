#ifndef LIST_H
#define LIST_H

// List
// Stores integer values inside
typedef int Data;

typedef char Operation;

struct ListItem
{
	Data data;
	Operation operation;
	ListItem* next;
};

struct List
{
	ListItem* first;
};

// Creates new list
List *list_create();

// Retrieves the first item from the list
ListItem* list_first(List* list);

// Extracts data from the list item
Data list_item_dt(const ListItem* item);

Operation list_item_op(const ListItem* item);

// Returns list item following after the specified one
ListItem* list_item_next(ListItem* item);

// Inserts new list item into the beginning
void list_insert(List* list, const char* str);

// Inserts new list item after the specified item
void list_insert_after(List* list, ListItem *item, const char* str);

// Deletes the list item following the specified one
// Should be O(1)
void list_erase_next(List* list, ListItem* item);

// Destroys the list and frees the memory
void list_delete(List* list);

bool is_dt(const char* str);

bool is_op(const char* str);

Data cast_dt(const char* str);

Operation cast_op(const char* str);

#endif