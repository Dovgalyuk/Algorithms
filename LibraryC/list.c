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
    while(list->root) list_erase_first(list);
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
    if (item) return item->prev;
    else return item;
}

ListItem *list_insert(List *list, Data data)
{
    ListItem *new_item = malloc(sizeof(ListItem));
    new_item->value = data;
    if (list->root) {
        new_item->next = list->root;
        new_item->prev = list->root->prev;
        new_item->prev->next = new_item;
        list->root->prev = new_item;
    } else {
        new_item->next = new_item;
        new_item->prev = new_item;
    }
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
    new_item->next->prev = new_item;
    return item->next;
}

ListItem *list_erase_first(List *list)
{
    ListItem *tmp = NULL;
    if (list->root) {
        tmp = list->root->next;

        tmp->prev = list->root->prev;
        list->root->prev->next = tmp;
        if (list->destructor)
            list->destructor(list->root->value);
        free(list->root);
        if (tmp != list->root)
            list->root = tmp;
        else
            list->root = NULL;
    }
    return list->root;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    ListItem *tmp = NULL;
    if (item)
    {
        tmp = item->next->next;
        tmp->prev = item;
        if (list->destructor)
            list->destructor(item->next->value);
        free(item->next);
        item->next = tmp;
    }
    return tmp;
}
