#pragma once


typedef int Data;
struct ListItem;

struct List;

List* list_create();
void list_delete(List* list);
ListItem* list_first(List* list);
ListItem* list_last(List* list);
Data list_item_data(ListItem* item);
ListItem* list_item_next(ListItem* item);
ListItem* list_item_prev(ListItem* item);
ListItem* list_insert(List* list, Data data);
ListItem* list_insert_after(List* list, ListItem* item, Data data);
ListItem* list_erase(List* list, ListItem* item);
ListItem* list_erase_after(List* list, ListItem* item);
bool list_empty(List* list);