#include <stdlib.h>
#include "list.h"

typedef struct ListItem
{
    struct ListItem* next;
    Data data;
} ListItem;

typedef struct List
{
    ListItem* head;
    FFree free_func;
} List;

List* list_create(FFree f)
{
    List* list = malloc(sizeof(List));
    if (list) {
        list->head = NULL;
        list->free_func = f;
    }
    return list;
}

void list_delete(List* list)
{
    ListItem* current = list->head;
    while (current) {
        ListItem* next = current->next;
        if (list->free_func) {
            list->free_func(current->data);
        }
        free(current);
        current = next;
    }
    free(list);
}


ListItem* list_first(List* list)
{
    return list->head;
}

Data list_item_data(const ListItem* item)
{
    return item->data;
}

ListItem* list_item_next(ListItem* item)
{
    return item->next;
}

ListItem* list_insert(List* list, Data data)
{
    ListItem* new_item = malloc(sizeof(ListItem));
    if (!new_item) return NULL;

    new_item->data = data;
    new_item->next = list->head;
    list->head = new_item;

    return new_item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!list || !item) return NULL;
    ListItem* newItem = (ListItem*)malloc(sizeof(ListItem));
    if (newItem) {
        newItem->data = data;
        newItem->next = item->next;
        item->next = newItem;
    }
    return newItem;
}

ListItem* list_erase_first(List* list)
{
    if (!list->head) return NULL;

    ListItem* to_delete = list->head;
    list->head = to_delete->next;

    if (list->free_func) { 
        list->free_func(to_delete->data);
    }

    free(to_delete);

    return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item)
{
    if (!item || !item->next) return NULL;

    ListItem* to_delete = item->next;
    item->next = to_delete->next;

    if (list->free_func) {
        list->free_func(to_delete->data);
    }

    free(to_delete);

    return item->next;
}
