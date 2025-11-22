#include <stdlib.h>
#include "list.h"

typedef struct ListItem {
    Data value;
    ListItem* next;
    ListItem* previous;
} ListItem;

typedef struct List {
    ListItem* first;
    FFree* freeFunc;
} List;

List *list_create(FFree f)
{
    List* newL = malloc(sizeof(List));
    if(!newL) return NULL;

    newL->first = NULL;
    newL->freeFunc = f;

    return newL;
}

void list_delete(List *list)
{
    if (list == NULL) 
        return; 

    ListItem* current = list->first;
    while (current != NULL) {
        ListItem* temp = current;
        current = current->next;
        if (list->freeFunc)
            list->freeFunc((void*)temp->value);
        free(temp);
    }
    free(list);
}

ListItem *list_first(List *list)
{
    if (list == NULL || list->first == NULL)
        return NULL;

    return list->first;
}

Data list_item_data(const ListItem *item)
{
    if(item == NULL)
        return (Data)0;

    return item->value;
}

ListItem *list_item_next(ListItem *item)
{
    if(item == NULL || item->next == NULL)
        return NULL;

    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if(item == NULL || item->previous == NULL)
        return NULL;

    return item->previous;
}

ListItem *list_insert(List *list, Data data)
{
    if(list == NULL )
        return NULL;

    ListItem* l = (ListItem*)malloc(sizeof(ListItem));
    if(!l) return NULL;

    l->value = data;
    l->previous = NULL;
    l->next = list->first;

    if (list->first != NULL) 
        list->first->previous = l;

    list->first = l;

    return l;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if(list == NULL )
        return NULL;

    if (list->first == NULL || item == NULL) 
        return list_insert(list, data);

    ListItem* l = (ListItem*)malloc(sizeof(ListItem));
    if(!l) return NULL;
    l->value = data;
    l->previous = item;
    l->next = item->next;

    if (item->next != NULL) 
        item->next->previous = l;
    item->next = l;

    return l;
}

ListItem *list_erase_first(List *list)
{
    if(list == NULL || list->first == NULL)
        return NULL;

    ListItem* temp = list->first;
    list->first = list->first->next;
    if (list->first != NULL)
        list->first->previous = NULL;

    list->freeFunc((void*)temp->value);
    free(temp);

    return list->first;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if(list == NULL || list->first == NULL )
        return NULL;

    if (item == NULL) 
        return list_erase_first(list);

    if (item->next == NULL)
        return NULL;

    ListItem* to_delete = item->next;
    item->next = to_delete->next;
    
    if (to_delete->next != NULL)
        to_delete->next->previous = item;

    list->freeFunc((void*)to_delete->value);
    free(to_delete);

    return item->next;
}
