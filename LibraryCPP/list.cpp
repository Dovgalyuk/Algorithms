#include "list.h"

List::List() {
    dummy = new ListItem{0, nullptr};
    dummy->next = dummy; // Кольцо
}

List::~List() {
    ListItem* current = dummy->next;
    while (current != dummy) {
        ListItem* next = current->next;
        delete current;
        current = next;
    }
    delete dummy;
}

ListItem* List::first() const {
    return (dummy->next == dummy) ? nullptr : dummy->next;
}

ListItem* List::insert_after(ListItem* item, int data) {
    ListItem* new_item = new ListItem{data, item->next};
    item->next = new_item;
    return new_item;
}

void List::erase_after(ListItem* item) {
    ListItem* to_erase = item->next;
    if (to_erase != dummy) {
        item->next = to_erase->next;
        delete to_erase;
    }
}
