#include <cstddef>
#include "list.h"

struct ListItem
{
    ListItem *prev;
    Data data;
    ListItem *next; 
};

struct List
{
    ListItem *head;
};

List *list_create()
{
    List *list = new List;
    list->head = NULL;
    return list;
}

void list_delete(List *list)
{
    if (!list) return;
    while(list->head != NULL){
        list_erase_first(list);
    }
    delete list;
}

ListItem *list_first(List *list)
{
    if(!list){
        return NULL;
    }
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
    if(!list){
        return NULL;
    }
    ListItem *newitem = new ListItem;
    newitem->data = data;
    newitem->next = list->head;
    newitem->prev = NULL;

    if(list->head!=NULL){
        list->head->prev = newitem;
    }
    list->head = newitem;
    return newitem;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!item){
        return list_insert(list, data); 
    }

    ListItem *newitem = new ListItem;
    newitem->data = data;
    newitem->prev = item;
    newitem->next = item->next;

    if (item->next != NULL) {
        item->next->prev = newitem;
    }
    item->next = newitem;
    return newitem;
}

ListItem *list_erase_first(List *list)
{
    if (!list || !list->head) {
        return NULL;
    }

    ListItem *oldhead = list->head;
    ListItem *newhead = oldhead->next;

    if(newhead != NULL){
        newhead->prev = NULL;
    }
    list->head = newhead;
    delete oldhead;
    return newhead;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
    if (!list || !list->head){
        return NULL;
    }
    if (!item){
        return list_erase_first(list); 
    }
    if (!item->next){
        return NULL;
    }

    ListItem *olditem = item->next;
    ListItem *newitem = olditem->next;

    item->next = newitem;
    if (newitem != NULL) {
        newitem->prev = item;
    }
    delete olditem;
    return newitem;
}

