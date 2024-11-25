
#include <cstddef>
#include "list.h"


struct ListItem {
	Data data;
	ListItem* next;
};

struct List {
	ListItem* head;
};
// Creates new list
List* list_create() {
	List* list = new List;
	list->head = nullptr;
	return list;
}
// Destroys the list and frees the memory
void list_delete(List* list) {
	ListItem* current_item = list->head;
	while (current_item != nullptr) {
		ListItem* next_item = current_item->next;
		delete current_item;
		current_item = next_item;
	}
	list->head = nullptr;
	delete list;
}
// Retrieves the first item from the list
ListItem* list_first(List* list) {
	return list->head;
}
// Extracts data from the list item
int list_item_data(const ListItem* item) {
	if (item == nullptr) {
		return NULL;
	}
	return item->data;
}
// Returns list item following after the specified one
ListItem* list_item_next(ListItem* item) {
	if (item == nullptr) {
		return nullptr;
	}
	return item->next;
}

// Returns previous element for the specified item.
// Not applicable for the singly linked lists.
ListItem* list_insert(List* list, Data data) {
	ListItem* item = new ListItem;
	item->data = data;
	item->next = list->head;
	list->head = item;
	return item;
}

// Inserts new list item into the beginning
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

// Deletes the first list item.
// Returns pointer to the item next to the deleted one.
ListItem* list_erase_first(List* list) {
	if (list == nullptr || list->head == nullptr) {
		return nullptr;
	}
	ListItem* first_item = list->head;
	list->head = first_item->next;
	delete first_item;
	return list->head;
}

// Deletes the list item following the specified one.
// Returns pointer to the item next to the deleted one.
// Should be O(1)
ListItem* list_erase_next(List* list, ListItem* item) {
	if (list == nullptr || item == nullptr || item->next == nullptr) {
		return nullptr;
	}
	ListItem* item_after = item->next;
	item->next = item_after->next;
	delete item_after;
	return item->next;
}