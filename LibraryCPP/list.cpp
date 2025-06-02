#include "list.h"
#include <stdexcept>

struct ListItem {
    Data data;
    ListItem* next;
    ListItem* prev;

    ListItem(Data d) : data(d), next(nullptr), prev(nullptr) {}
};

struct List {
    ListItem* head;

    List() : head(nullptr) {}
    ~List() {
        if (!head) return;
        ListItem* current = head->next;
        while (current != head) {
            ListItem* nextItem = current->next;
            delete current;
            current = nextItem;
        }
        delete head;
        head = nullptr;
    }
};

List* list_create() {
    return new List();
}

void list_delete(List* list) {
    delete list;
}

ListItem* list_first(List* list) {
    if (!list) return nullptr;
    return list->head;
}

Data list_item_data(const ListItem* item) {
    if (!item) throw std::invalid_argument("Null pointer in list_item_data");
    return item->data;
}

ListItem* list_item_next(ListItem* item) {
    if (!item) return nullptr;
    return item->next;
}

ListItem* list_item_prev(ListItem* item) {
    if (!item) return nullptr;
    return item->prev;
}

ListItem* list_insert(List* list, Data data) {
    return list_insert_after(list, nullptr, data);
}

ListItem* list_insert_after(List* list, ListItem* item, Data data) {
    if (!list) throw std::invalid_argument("Null list in list_insert_after");

    ListItem* newItem = new ListItem(data);

    if (!list->head) {
        // пустой список
        newItem->next = newItem;
        newItem->prev = newItem;
        list->head = newItem;
    } else if (!item) {
        // вставка в начало
        ListItem* tail = list->head->prev;
        newItem->next = list->head;
        newItem->prev = tail;
        tail->next = newItem;
        list->head->prev = newItem;
        list->head = newItem;
    } else {
        // вставка после item
        newItem->next = item->next;
        newItem->prev = item;
        item->next->prev = newItem;
        item->next = newItem;
    }

    return newItem;
}

ListItem* list_erase_first(List* list) {
    return list_erase_next(list, nullptr);
}

ListItem* list_erase_next(List* list, ListItem* item) {
    if (!list || !list->head) return nullptr;

    ListItem* toDelete;

    if (!item) {
        toDelete = list->head;
    } else {
        toDelete = item->next;
    }

    if (toDelete == toDelete->next) {
        // один элемент в списке
        list->head = nullptr;
        delete toDelete;
        return nullptr;
    } else {
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        if (toDelete == list->head) {
            list->head = toDelete->next;
        }
        ListItem* nextItem = toDelete->next;
        delete toDelete;
        return nextItem;
    }
}
