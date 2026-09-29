#include <cstddef>
#include "list.h"

struct ListItem 
{
	Data data;
	ListItem* next;
};

struct List
{
	ListItem* head;
	size_t size;
};

List* list_create() {
	List* list = new List;
	list->head = NULL;
	list->size = 0;
	return list;
}

void list_delete(List* list) {
	if (list == NULL) {
		return;
	}

	ListItem* tekushciy = list->head;
	while (tekushciy != NULL) {
		ListItem* next = tekushciy->next;
		delete tekushciy;
		tekushciy = next;
	}
	delete list;
}

ListItem* list_first(List* list) {
	if (list == NULL) {
		return NULL;
	}
	return list->head;
}

ListItem* list_last(List* list) {
	if (list == NULL && list->head == NULL) {
		return NULL;
	}
	ListItem* tekushciy = list->head;
	while (tekushciy->next != NULL) {
		tekushciy = tekushciy->next;
	}
	return tekushciy;
}


Data list_item_data(const ListItem* item) {
	if (item == NULL) {
		return (Data)0;
	}
	return item->data;
}

ListItem* list_item_next(ListItem* item) {
	if (item == NULL) {
		return NULL;
	}
	return item->next;
}

ListItem* list_item_prev(ListItem* item) {
	(void)item;
	return NULL;
}

ListItem* list_insert(List* list, Data data) {
	return list_insert_after(list, NULL, data);
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
	if (list == NULL) {
		return NULL;
	}
	ListItem* mesto = new ListItem;
	mesto->data = data;

	if (item == NULL) {
		mesto->next = list->head;
		list->head = mesto;
	}
	else {
		mesto->next = item->next;
		item->next = mesto;
	}
	list->size++;
	return mesto;
}

ListItem* list_erase_first(List* list) {
	if (list == NULL || list->head == NULL) {
		return NULL;
	}

	ListItem* old = list->head;
	list->head = old->next;
	delete old;
	list->size--;
	return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item) {
	if (list == NULL || list->head == NULL) {
		return NULL;
	}

	if (item == NULL) {
		return list_erase_first(list);
	}

	ListItem* udalenie = item->next;
	if (udalenie == NULL) {
		return NULL;
	}

	item->next = udalenie->next;
	delete udalenie;
	list->size--;
	return item->next;
}