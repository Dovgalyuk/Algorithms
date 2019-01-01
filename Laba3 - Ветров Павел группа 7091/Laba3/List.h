#ifndef LIST_H
#define LIST_H

typedef int Data;

struct List;
struct ListItem;


List *list_create();
void list_delete(List *list);
ListItem *list_first(List *list);
Data *list_item_data(ListItem *item);
ListItem *list_item_next(ListItem *item);
ListItem *list_insert(List *list, Data data);
ListItem *list_erase_first(List *list);
ListItem *list_erase_item(List *list, Data value);
bool list_item_exist(List *list, Data value);
Data *list_item_weight(List *list, Data value);

#endif
