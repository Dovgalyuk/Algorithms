#include <stdlib.h>
#include "list.h"

typedef struct ListItem {
    Data value;
    ListItem* next;
    ListItem* last;
} ListItem;

typedef struct List {
    ListItem* first;
    size_t size;
    FFree* freeFunc;
} List;

List *list_create(FFree f)
{
    List* newL = malloc(sizeof(List));
    if(!newL) return NULL;

    newL->first = NULL;
    newL->size = 0;
    newL->freeFunc = f;

    return newL;
}

void list_delete(List *list)
{
    ListItem* current = list->first;
    while (current != NULL) {
        ListItem* temp = current;
        current = current->next;
        list->freeFunc((void*)temp->value);
        free(temp);
    }
    free(list);
}

ListItem *list_first(List *list)
{
    if (list == NULL || list->size == 0)
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
    if(item == NULL || item->last == NULL)
        return NULL;

    return item->last;
}

ListItem *list_insert(List *list, Data data)
{
    if(list == NULL )
        return NULL;

    ListItem* l = (ListItem*)malloc(sizeof(ListItem));
    if(!l) return NULL;

    l->value = data;
    l->last = NULL;
    l->next = list->first;

    if (list->size != 0) 
        list->first->last = l;

    list->first = l;
    list->size++;

    return l;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if(list == NULL )
        return NULL;

    if (list->size == 0 || item == NULL) 
        return list_insert(list, data);

    ListItem* l = (ListItem*)malloc(sizeof(ListItem));
    if(!l) return NULL;
    l->value = data;
    l->last = item;
    l->next = item->next;

    ListItem* nextCurrent = item->next;

    if (item->next != NULL) 
        item->next->last = l;
    item->next = l;

    list->size++;

    return l;
}

ListItem *list_erase_first(List *list)
{
    if(list == NULL || list->size == 0)
        return NULL;

    ListItem* temp = list->first;
    list->first = list->first->next;
    if (list->first != NULL)
        list->first->last = NULL;

    list->freeFunc((void*)temp->value);
    free(temp);

    list->size--;

    return list->first;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if(list == NULL || list->size == 0 )
        return NULL;

    if (list->size == 1 || item == NULL) 
        return list_erase_first(list);

    if (item->next == NULL)
    return NULL;

    ListItem* current = item->next;

    if (item->next->next != NULL)
        item->next->next->last = item;
    item->next= item->next->next;

    list->freeFunc((void*)current->value);
    free(current);

    list->size--;

    return item->next;
}
