#include <stdlib.h>
#include "list.h"

typedef struct ListItem
{
    Data value;
    ListItem *prev;
    ListItem *next;
} ListItem;

typedef struct List
{
    FFree *destructor;
    ListItem *root;
} List;

List *list_create(FFree f)
{
    List *new_list = malloc(sizeof(List));
    new_list->destructor = f;
    new_list->root = NULL;
    return new_list;
}

void list_delete(List *list)
{
    while(list->root != NULL) list_erase_first(list);
    free(list);
}

ListItem *list_first(List *list)
{
    return list->root;
}

Data list_item_data(const ListItem *item)
{   if (item) return (Data) item->value;
    else return (Data) 0;
}

ListItem *list_item_next(ListItem *item)
{   if (item) return item->next;
    else return item;
}

ListItem *list_item_prev(ListItem *item)
{
    return item->prev;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *new_item = malloc(sizeof(ListItem));
    new_item->value = data;
    new_item->next = list->root;
    new_item->prev = NULL;
    list->root = new_item;
    return list->root;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    ListItem *new_item = malloc(sizeof(ListItem));
    new_item->value = data;
    new_item->next = item->next;
    new_item->prev = item;
    item->next = new_item;
    return item->next;
}

ListItem *list_erase_first(List *list)
{
    ListItem *tmp = NULL;
    if (list->root)
    {
        tmp = list->root->next;
        if (tmp)
            tmp->prev = NULL;
        if (list->destructor)
            list->destructor(list->root->value);
        free(list->root);
        list->root = tmp;
    }
    return tmp;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *tmp = NULL;
    if (item->next)
    {
        tmp = item->next->next;
        if (tmp) tmp->prev = item;
        list->destructor(item->next->value);
        free(item->next);
        item->next = tmp;
    }
    return tmp;
}
