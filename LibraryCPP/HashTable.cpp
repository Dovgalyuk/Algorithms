#include "HashTable.h"
#include "../LibraryCPPTemplate/array.h"

using namespace std;

//----------------------- Structs -----------------------//
HashTable::HashTable() {
	this->capacity = 61;
	this->cnt_del = 0;
	this->elements_size = 0;
	this->elements = new Array<Element>(capacity);
}
HashTable::~HashTable() { delete[] elements; }
Element::Element(string key, string value, bool deleted = false) {
	this->key = key;
	this->value = value;
	this->deleted = deleted;
}
Element::Element() {
	this->key = "";
	this->value = "";
	this->deleted = false;
}
//-------------------------------------------------------//

//-------------------- Hash Functions -------------------//
int FirstHashFunction(string key, int capacity) {
	int hash = 0;
	unsigned long long unique_value = 1;
	for (size_t i = 0; i < key[i]; i++){
		hash = (hash * unique_value + key[i]) % capacity;
		unique_value *= 23;
	}
	return hash % capacity;
}
int SecondHashFunction(string key, int capacity) {
	int hash = 0;
	unsigned long long unique_value = 1;
	for (size_t i = 0; i < key[i]; i++) {
		hash = (hash * unique_value + key[i]) % capacity;
		unique_value *= 27;
	}
	int result = hash % capacity;
	if (result % 2 == 0) return result + 1;
	return result;
}
//-------------------------------------------------------//

//---------------- Functions for solution ---------------//
void add(string key, string value, HashTable* table) {
	int capacity = table->capacity;
	int first_index = FirstHashFunction(key, capacity);
	int final_hash_index = first_index;
	if (table->elements->get(final_hash_index).key.size() != 0 && table->elements->get(final_hash_index).deleted == false) {
		int second_index = SecondHashFunction(key, capacity);
		int iter = 1;
		final_hash_index = (first_index + iter * second_index) % capacity;
		while (table->elements->get(final_hash_index).key.size() != 0 && table->elements->get(final_hash_index).deleted == false) {
			iter++;
			final_hash_index = (first_index + iter * second_index) % capacity;
		}
	}
	table->elements->set(final_hash_index, Element(key, value));
	table->elements_size++;

	
	if (check_capacity(table->elements_size, table->capacity)) resize(table);
}
void resize(HashTable* table) {
	Array<Element>* new_elements = new Array<Element>(table->capacity * 2);
	for (size_t i = 0; i < table->capacity; i++){
		if (table->elements->get(i).key.size() != 0 && table->elements->get(i).deleted == false) {
			int first_index = FirstHashFunction(table->elements->get(i).key, table->capacity);
			int final_hash_index = first_index;
			if (new_elements->get(final_hash_index).key.size() != 0) {
				int second_index = SecondHashFunction(table->elements->get(i).key, table->capacity);
				int iter = 1;
				final_hash_index = (first_index + iter * second_index) % table->capacity;
				while (new_elements->get(final_hash_index).key.size() != 0) {
					iter++;
					final_hash_index = (first_index + iter * second_index) % table->capacity;
				}
			}
			new_elements->set(final_hash_index, table->elements->get(i));
		}
	}
	table->capacity *= 2;
	table->elements = new_elements;
}
void del(string key, HashTable* table) {
	int index_to_delete = find_index(key, table);
	if (index_to_delete == -1) return;
	table->elements_size--;
	table->cnt_del++;
	table->elements->set(index_to_delete, Element(table->elements->get(index_to_delete).key, table->elements->get(index_to_delete).value, true));
}
int find_index(string key, HashTable* table) {
	int hash = FirstHashFunction(key, table->capacity);
	int final_hash_index = hash;
	if (table->elements->get(final_hash_index).key.size() != 0) {
		int hash2 = SecondHashFunction(key, table->capacity);
		int iter = 0;
		final_hash_index = (hash + iter * hash2) % table->capacity;
		while (table->elements->get(final_hash_index).key.size() != 0 && table->elements->get(final_hash_index).deleted == false) {
			if (compare_strings(key, table->elements->get(final_hash_index).key)) return final_hash_index;
			iter++;
			final_hash_index = (hash + iter * hash2) % table->capacity;			
		}
	}
	return -1;
}
string find(string key, HashTable* table) {
	int index = find_index(key, table);
	if (index == -1) return "UNKNOWN VALUE EXCEPTION\n";
	else return table->elements->get(index).value;
}
bool compare_strings(string first, string second) {
	if (first.size() != second.size()) return false;
	for (size_t i = 0; i < first.size(); i++) { if (first[i] != second[i]) return false; }
	return true;
}
bool check_capacity(int size, int capacity) { return size >= capacity / 2; }
//-------------------------------------------------------//
