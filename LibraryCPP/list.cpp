#include <iostream>
#include "list.h"

using namespace std;


struct ListItem {
	Data data;
	ListItem* next;
	ListItem* prev;
	ListItem(Data data, ListItem* next = nullptr, ListItem* prev = nullptr) {
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
};
struct List {
	ListItem* head;
	ListItem* last;

	List() {
		this->head = nullptr;
		this->last = nullptr;
	}
	~List() {
		ListItem* current = head;
		while (current) {
			ListItem* toDelete = current;
			current = toDelete->next;
			delete toDelete;
		}
	}
};

List* list_create() { return new List(); }
void list_delete(List* list) { delete list; }
ListItem* list_first(List* list) { return list->head; }
ListItem* list_last(List* list) { return list->last; }
Data list_item_data(ListItem* item) { return item->data; }
ListItem* list_item_next(ListItem* item) { return item->next; }
ListItem* list_item_prev(ListItem* item) { return item->prev; }
ListItem* list_insert(List* list, Data data) {
	if (list_empty(list)) {
		list->head = new ListItem(data);
		return list->last = list->head;
	}
	else {
		ListItem* add_item = new ListItem(data, list->head, nullptr);
		list->head->prev = add_item;
		return list->head = add_item;
	}
}
ListItem* list_insert_after(List* list, ListItem *item, Data data) {
	if (list_empty(list)) {
		list->head = new ListItem(data);
		return list->last = list->head;
	}
	else if (item == list->head) {
		ListItem* add_item = new ListItem(data, list->head->next, list->head);
		list->head->next = add_item;
		return add_item;
	}
	else if (item == list->last) {
		ListItem* add_item = new ListItem(data, nullptr, item);
		item->next = add_item;
		return list->last = add_item;
	}
	else {
		ListItem* add_item = new ListItem(data, item->next, item);
		item->next = add_item;
		item->next->prev = add_item;
		return add_item;
	}
}
ListItem* list_erase(List* list, ListItem* item) {
	if (list_empty(list)) throw "Exception empty list\n";
	else {
		if (list_first(list) == item) {
			ListItem* curr = list->head;
			list->head = curr->next;
			delete curr;
			return list_first(list);
		}
		else if (list_last(list) == item) {
			list->last = item->prev;
			delete item;
			return list->last->next = nullptr;
		}
		else {
			ListItem* next = item->next;
			item->prev->next = next;
			next->prev = item->prev;
			delete item;
			return next;
		}
	}
}
ListItem* list_erase_after(List* list, ListItem* item) {
	if (list_empty(list)) throw "Exception empty list\n";
	else {
		ListItem* toDelete = item->next;
		item->next = toDelete->next;
		toDelete->next->prev = toDelete->prev;
		return item->next;
	}
}
bool list_empty(List* list) { return (list->head) ? false : true; }




