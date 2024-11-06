#include <cstddef>
#include <string>
#include "list.h"

struct ListItem {
	Data data;
	ListItem* next;
};

struct List {
	ListItem* head;
};

List* list_create() {
	List* list = new List;
	list->head = nullptr;
	return list;
}

void list_delete(List* list) {
	ListItem* cur_item = list->head;
	while (cur_item != nullptr) {
		ListItem* next_item = cur_item->next;
		delete cur_item;
		cur_item = next_item;
	}
	list->head = nullptr;
	delete list;
}

ListItem* list_first(List* list) {
	return list->head;
}

Data list_item_data(const ListItem* item) {
	if (item == nullptr) {
		return "";
	}
	return item->data;
}

ListItem* list_item_next(ListItem* item) {
	if (item == nullptr) {
		return nullptr;
	}
	return item->next;
}

ListItem* list_insert(List* list, Data data) {
	ListItem* item = new ListItem;
	item->data = data;
	item->next = list->head;
	list->head = item;
	return item;
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
	if (list == nullptr || item == nullptr) {
		return nullptr;
	}
	ListItem* item_after = new ListItem;
	item_after->data = data;
	item_after->next = item->next;
	item->next = item_after;
	return item_after;
}

ListItem* list_erase_first(List* list) {
	if (list == nullptr || list->head == nullptr) {
		return nullptr;
	}
	ListItem* first_item = list->head;
	list->head = first_item->next;
	delete first_item;
	return list->head;
}

ListItem* list_erase_next(List* list, ListItem* item) {
	if (list == nullptr || item == nullptr || item->next == nullptr) {
		return nullptr;
	}
	ListItem* item_after = item->next;
	item->next = item_after->next;
	delete item_after;
	return item->next;
}