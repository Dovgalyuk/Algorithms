#include <stdlib.h>
#include "list.h"

typedef struct ListItem {
    struct ListItem *prev;
    struct ListItem *next;
    Data d;
} ListItem;

typedef struct List {
    ListItem *head;
    ListItem *tail;
    FFree *freefunc;
} List;

List *list_create(FFree f)
{
    List *list = malloc(sizeof(List)); 
    if (!list) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->freefunc = f;
    return list;
}

void list_delete(List *list)
{
    if (!list) return;
    ListItem *point = list->head;
    while (point){
        ListItem *next = point->next;
        if (list->freefunc) {
            list->freefunc((void*)point->d);
        }
        free(point);
        point = next;
    }
    
    free(list);
}

ListItem *list_first(List *list)
{
    if (!list) return NULL;

    return list->head;
}

ListItem *list_last(List *list)
{
    if (!list) return NULL;

    return list->tail;
}

/* проверка существования item перед вызовом обязтельна.
у нас 0 может хранится как данные, потому надо
*/
Data list_item_data(const ListItem *item)
{
    if (!item) return (Data)0; // я бы не вставлял это вообще, но по шаблону выглядит что нужно так
    return item->d;
}

ListItem *list_item_next(ListItem *item)
{
    if (!item) return NULL;

    return item->next;
}

ListItem *list_item_prev(ListItem *item)
{
    if (!item) return NULL;

    return item->prev;
}

ListItem *list_insert(List *list, Data data) // new head
{
    if (!list) return NULL;

    ListItem *item = malloc(sizeof(ListItem));
    if (!item) return NULL;
    item->d = data;
    item->prev = NULL;
    item->next = list->head;
    if (list->head) list->head->prev = item;
    else list->tail = item;
    
    list->head = item;
    return item;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list) return NULL;
    if (!item) return list_insert(list, data);
    ListItem *newitem = malloc(sizeof(ListItem));
    if (!newitem) return NULL;
    newitem->d = data;
    newitem->prev = item;
    newitem->next = item->next;
    item->next = newitem;
    if (newitem->next) newitem->next->prev = newitem;
    else list->tail = newitem;
    return newitem;
}

ListItem *list_erase_first(List *list) // del head of list, return new head
{
    if (!list || !list->head) return NULL;
    ListItem *del = list->head;
    list->head = del->next;
    if (list->freefunc) {
        list->freefunc((void*)del->d);
    }
    if (list->head) list->head->prev = NULL;
    else list->tail = NULL;
    free(del);
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item) // del next to given, return new next
{
    if (!list) return NULL;
    if (!item) return list_erase_first(list);
    ListItem *del = item->next;
    if (del){ 
        item->next = del->next;
        if (del->next) del->next->prev = item;
        else list->tail = item;
        if (list->freefunc) {
            list->freefunc((void*)del->d);
        }
        free(del);
    }
    return item->next;
}
