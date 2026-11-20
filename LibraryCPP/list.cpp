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
	ListItem* tail;
};

List* list_create() {
	List* list = new List;
	list->head = NULL;
	list->tail = NULL;
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
	if (list == NULL) {
		return NULL;
	}
	return list->tail;
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

		if (list->tail == NULL) {
			list->tail = mesto;
		}
	}
	else {
		mesto->next = item->next;
		item->next = mesto;

		if (item == list->tail) {
			list->tail = mesto;
		}
	}
	return mesto;
}

ListItem* list_erase_first(List* list) {
	if (list == NULL || list->head == NULL) {
		return NULL;
	}

	ListItem* old = list->head;
	list->head = old->next;
	delete old;

	if (list->head == NULL) {
		list->tail = NULL;
	}

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

	if (udalenie == list->tail) {
		list->tail = item;
	}

	return item->next;
}