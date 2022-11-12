#ifndef LIST_H
#define LIST_H

// List
// Stores integer values inside
typedef int Data;

struct DLList;
struct DLListItem;

DLList* list_create();

void list_delete(DLList* list);

DLListItem* list_first(DLList* list);

Data list_item_data(const DLListItem* item);

DLListItem* list_item_next(DLListItem* item);

DLListItem* list_item_prev(DLListItem* item);

DLListItem* list_insert(DLList* list, Data data);

DLListItem* list_insert_after(DLList* list, DLListItem* item, Data data);

DLListItem* list_erase(DLList* list, DLListItem* item);

DLListItem* list_erase_next(DLList* list, DLListItem* item);

DLListItem* list_erase_first(DLList* list);

#endif
