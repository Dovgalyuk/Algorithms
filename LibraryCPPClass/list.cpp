#include "list.h"


List::List() {}

List::List(const List& a) { (void)a; }

List& List::operator=(const List& a) { (void)a; return *this; }

List::~List() {}

List::Item* List::first() { return nullptr; }

List::Item* List::insert(Data data) { (void)data; return nullptr; }

List::Item* List::insert_after(Item* item, Data data) { (void)item; (void)data; return nullptr; }

List::Item* List::erase_first() { return nullptr; }

List::Item* List::erase_next(Item* item) { (void)item; return nullptr; }
