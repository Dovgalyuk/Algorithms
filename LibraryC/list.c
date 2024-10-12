#include <stdlib.h>
#include "list.h"

typedef struct ListItem
{
    Data data;
    struct ListItem *next;
    struct ListItem *prev;
} ListItem;

typedef struct List
{
    ListItem *head;
    ListItem *tail;
    FFree *free_func;
} List;

List *list_create(FFree f)
{
    List *list = malloc(sizeof(List));
    if (list == NULL) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->free_func = f;
    return list;
    
}

void list_delete(List *list)
{
    ListItem *current = list->head;
    while (current != NULL)
    {
        ListItem *next = current->next;
        if (list->free_func != NULL)
            list->free_func(current->data);
        free(current);
        current = next;
    }
    free(list);
    
}

ListItem *list_first(List *list)
{
    return list->head;
}

Data list_item_data(const ListItem *item)
{
    return item->data;
}

ListItem *list_item_next(ListItem *item)
{
    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *new_item = malloc(sizeof(ListItem));
    if (new_item == NULL) return NULL;
    new_item->data = data;
    new_item->next = list->head;
    new_item->prev = NULL;
    if (list->head != NULL)
        list->head->prev = new_item;
    list->head = new_item;
    if (list->tail == NULL)
        list->tail = new_item;
    return new_item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *new_item = malloc(sizeof(ListItem));
    if (new_item == NULL) return NULL;
    new_item->data = data;
    new_item->next = item->next;
    new_item->prev = item;
    if (item->next != NULL)
        item->next->prev = new_item;
    item->next = new_item;
    if (item == list->tail)
        list->tail = new_item;
    return new_item;
}

ListItem *list_erase_first(List *list)
{
    if (list->head == NULL) return NULL;
    ListItem *next_item = list->head->next;
    if (list->free_func != NULL)
        list->free_func(list->head->data);
    free(list->head);
    list->head = next_item;
    if (list->head == NULL)
        list->tail = NULL;
    else
        list->head->prev = NULL;
    return next_item;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (item->next == NULL) return NULL;
    ListItem *next_item = item->next->next;
    if (list->free_func != NULL)
        list->free_func(item->next->data);
    free(item->next);
    item->next = next_item;
    if (next_item != NULL)
        next_item->prev = item;
    else
        list->tail = item;
    return next_item;
}
