#include <stdlib.h>
#include "list.h"

struct ListItem {
	ListItem *Prev = NULL, *Next = NULL; //Указатели на след и пред элементы списка
	int data; //данные элемента списка

};

struct List {
	ListItem *Head = NULL;
};

// �������� ������
List *list_create() {
	List* list = new List; // инииализация списка
	return list;
}

// �������� ������
void list_delete(List *list) {
	if (list == NULL) {
		return;
	}
	ListItem* item = list_first(list);
	while(item){
		ListItem* temp = item;
		item = item->Next;
		delete temp;
	}
	delete list;
}

// �������� ������ ������� ������
ListItem *list_first(List *list) {

	if (list == NULL) {
		return NULL;
	}
	return list->Head; //
}

// ������� ������ �� �������� ������
int list_item_data(ListItem *item) {
	if (item == NULL) {
		return 0;
	}
	return item->data;
}

// �������� ��������� ������� ������
ListItem *list_item_next(ListItem *item) {

	if (item == NULL) {
		return NULL;
	}
	return item->Next;
}

// �������� ���������� ������� ������
ListItem *list_item_prev(ListItem *item) {
	if (item == NULL) {
		return NULL;
	}
	return item->Prev;
}

// �������� ������ � ������ ������
ListItem *list_insert(List *list, int data) {
	if (list == NULL) {
		return NULL;
	}
	ListItem *item = new ListItem;
	item->data = data;
	item->Next = list->Head;
	if (list->Head != NULL) {
		list->Head->Prev = item;
	}
	list->Head = item;
	return item;
}

// �������� ������ ����� ��������� ��������
ListItem *list_insert_after(List *list, ListItem *item, int data) {
	if (item == NULL || list == NULL) {
		return NULL;
	}
	ListItem *item2 = new ListItem;
	item2->data = data;
	item2->Prev = item;
	item2->Next = item->Next;

	if (item2->Next != NULL) {
		item2->Next->Prev = item2;
	}
	item->Next = item2;
	return item2;
}

// ������� �������� ������� ������
ListItem *list_erase(List *list, ListItem *item) {
	if (item == NULL || list == NULL) {
		return NULL;
	}
	ListItem *prev = item->Prev;
	ListItem *next = item->Next;
	if (item == list->Head) {
		list->Head = next;
		if (list->Head != NULL) {
			list->Head->Prev = NULL;
		}

	} else {
		prev->Next = next;
		if (next != NULL) {
			next->Prev = prev;
		}
	}
	delete item;
	return next;
}

// ������� ������� ������, ��������� �� ��������
ListItem *list_erase_next(List *list, ListItem *item) {
	if (item == NULL || list == NULL) {
		return NULL;
	}
	if (item->Next == NULL) {
		return NULL;
	}
	if (item->Next->Next == NULL) {
		ListItem *next = item->Next;
		item->Next = NULL;
		delete next;
		return NULL;
	}
	ListItem *next = item->Next;
	ListItem *nextnext = item->Next->Next;
	nextnext->Prev = item;
	item->Next = nextnext;
	delete next;
	return nextnext;
}
