#include <stdlib.h>
#include "list.h"

typedef struct ListItem {
    Data data;
	struct ListItem *next;
	struct ListItem *prev;
} ListItem;

typedef struct List {
    ListItem *head;
	ListItem *tail;
	FFree *freeFn;
} List;

List *list_create(FFree f)
{
    List *list = (List*)malloc(sizeof(List));
	if (!list) return NULL;
	list->head = NULL;
	list->tail = NULL;
	list->freeFn = f;
	return list;
}

void list_delete(List *list)
{
    if (!list) return;
	ListItem *cur = list->head;
	while (cur) {
		ListItem *next = cur->next;
        free(cur);
		cur = next;
	}
	free(list);
}

ListItem *list_first(List *list) {
    if (list) {
        return list->head;
    } else {
        return NULL;
    }
}

Data list_item_data(const ListItem *item) {
    if (item) {
        return item->data;
    } else {
        return (Data)0;
    }
}

ListItem *list_item_next(ListItem *item) {
    if (item) {
        return item->next;
    } else {
        return NULL;
    }
}

ListItem *list_item_prev(ListItem *item) {
    if (item) {
        return item->prev;
    } else {
        return NULL;
    }
}

ListItem *list_insert(List *list, Data data)
{
    if (!list) return NULL;
	ListItem *node = (ListItem*)malloc(sizeof(ListItem));
    node->data = data;
    node->next = list->head;
    node->prev = NULL;

    if (list->head) {
        list->head->prev = node;
    } else {
        list->tail = node;
    }

    list->head = node;
    return node;
}

ListItem *list_insert_after(List *list, ListItem *item, Data data)
{
    if (!list) return NULL;
	ListItem *node = (ListItem*)malloc(sizeof(ListItem));
    node->data = data;
    node->next = item->next;
    node->prev = item;
    if (item->next) {
        item->next->prev = node;
    } else {
        list->tail = node;
    }
	item->next = node;

	return node;

}

ListItem *list_erase_first(List *list)
{
    if (!list || !list->head) return NULL;
    
    ListItem* fordelete = list->head;
    ListItem* newfirst = fordelete->next;

    list->head = newfirst;

    if(newfirst){
        newfirst->prev=NULL;
    } else {
        list->tail = NULL;
    }

	if (list->freeFn) {
		list->freeFn((void*)fordelete->data);
	}
	free(fordelete);
    return list->head;
}

ListItem *list_erase_next(List *list, ListItem *item)
{
	if (!list) return NULL;
	if (item == NULL) return list_erase_first(list);
	if (!item->next) return NULL;

    ListItem* fordelete = item->next;
    ListItem* newnext = fordelete->next;

    item->next = newnext;

    if (newnext) {
        newnext->prev = item;
    } else {
        list->tail = item;
    }

	if (list->freeFn) {
		list->freeFn((void*)fordelete->data);
	}
	free(fordelete);
    return item->next;
}
