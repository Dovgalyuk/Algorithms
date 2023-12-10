#include <cstddef>
#include <algorithm>
#include "list.h"

List::List() : head(nullptr) {}

List::List(const List &a) : head(nullptr) {
  Item* node = a.head;
  while (node != nullptr) {
      insert(node->data());
      node = node->next();
  }
}

List &List::operator=(const List &a) {
  if (this != &a) {
      List temp(a);
      std::swap(head, temp.head);
  }
  return *this;
}

List::~List() {
  while (head != nullptr) {
      erase_first();
  }
}

List::Item *List::first() {
 return head;
}

List::Item *List::insert(Data data) {
 Item* newItem = new Item;
 newItem->data() = data; 
 newItem->next() = head; 
 head = newItem;
 return newItem;
}

List::Item *List::insert_after(Item *item, Data data) {
 if (item == nullptr) {
     return nullptr;
 }
 Item* newItem = new Item;
 newItem->data() = data; 
 newItem->next() = item->next();
 item->next() = newItem;
 return newItem;
}

List::Item *List::erase_first() {
 if (head == nullptr) {
     return nullptr;
 }
 Item* nextItem = head->next();
 delete head;
 head = nextItem;
 return nextItem;
}

List::Item *List::erase_next(Item *item) {
 if (item == nullptr || item->next() == nullptr) {
     return nullptr;
 }
 Item* nextItem = item->next()->next();
 delete item->next();
 item->next() = nextItem; // используйте метод next() для установки значения
 return nextItem;
}
