#include "stack.h"

Stack::Stack() {}

Stack::Stack(const Stack &a) : list(a.list) {
  // implement or disable this function
}

Stack &Stack::operator=(const Stack &a) {
  // implement or disable this function
  if (this != &a) {
    list = a.list;
  }
  return *this;
}

Stack::~Stack() {
  // Деструктор в списке выполняет эту работу
}

void Stack::push(Data data) { list.insert(data); }

Data Stack::get() const {
  if (empty()) {
    return Data();
  }
  return list.first()->data();
}

void Stack::pop() {
  if (!empty()) {
    list.erase_first();
  }
}

bool Stack::empty() const { return list.first() == nullptr; }
