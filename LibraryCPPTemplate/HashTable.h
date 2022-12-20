#pragma once

#include <iostream>
#include "array.h"

using namespace std;

int FirstHashFunction(const string& key, int capacity) {
	int hash = 0;
	unsigned long long unique_value = 1;
	for (size_t i = 0; key[i]; i++) {
		hash = (hash * unique_value + key[i]) % capacity;
		unique_value *= 23;
	}
	return hash % capacity;
}
int SecondHashFunction(const string& key, int capacity) {
	int hash = 0;
	unsigned long long unique_value = 1;
	for (size_t i = 0; key[i]; i++) {
		hash = (hash * unique_value + key[i]) % capacity;
		unique_value *= 27;
	}
	int result = hash % capacity;
	if (result % 2 == 0) return result + 1;
	return result;
}


class HashTable {
	struct Element {
		string key;
		string value;
		bool deleted = false;
		Element() {
			this->key = "";
			this->value = "";
			this->deleted = "false";
		}
		Element(string key, string value, bool deleted = false) {
			this->key = key;
			this->deleted = deleted;
			this->value = value;
		}
	};

	Array<Element>* elements;
	int capacity;
	int size;
	int count_deleted;

	bool check_capacity() { return this->size + this->count_deleted >= this->capacity / 2; }
	int algorithm(string key, Array<Element>* elements, bool& not_found) {
		int first_hash = FirstHashFunction(key, this->capacity);
		int final_hash = first_hash;
		if (elements->get(final_hash)->key.size() != 0 && elements->get(final_hash)->deleted == false) {
			if (not_found && (key == elements->get(final_hash)->key)) {not_found = false; return final_hash; }
			int second_hash = SecondHashFunction(key, this->capacity);
			int iter = 1;
			final_hash = (first_hash + iter * second_hash) % capacity;
			while (elements->get(final_hash)->key.size() != 0 && elements->get(final_hash)->deleted == false) {
				if (not_found && key == elements->get(final_hash)->key) {not_found = false; return final_hash;}
				iter++;
				final_hash = (first_hash + iter * second_hash) % capacity;
			}
		}
		return final_hash;
	}
	void resize() {
		this->size = 0;
		Array<Element>* new_elements = new Array<Element>(capacity * 4);
		for (size_t i = 0; i < this->capacity; i++) {
			string key = this->elements->get(i)->key;
			string value = this->elements->get(i)->value;
			if (key.size() != 0) {
				bool not_found = false;
				int index = algorithm(key, new_elements, not_found);
				new_elements->set(index, Element(key, value));
				this->size++;
			}
		}
		this->elements = new_elements;
		this->capacity *= 4;
	}
	int find_index(string key) {
		bool not_found = true;
		int hash_index = algorithm(key, this->elements, not_found);
		if (not_found) return -1;
		return hash_index;
	}
public:
	HashTable() {
		this->capacity = 16;
		this->size = 0;
		this->count_deleted = 0;
		this->elements = new Array<Element>(capacity);
	}
	~HashTable() {
		delete this->elements;
	}
		
	void add(string key, string value) {
		bool not_found = false;
		int final_hash = algorithm(key, this->elements, not_found);
		elements->set(final_hash, Element(key, value));
		this->size++;	
		if (check_capacity()) resize();
	}
	void del(string key) {
		int index_to_delete = find_index(key);
		if (index_to_delete == -1) return;
		this->size--;
		this->count_deleted++;
		this->elements->get(index_to_delete)->deleted = true;
	}
	string find(string key) {
		int index = find_index(key);
		if (index == -1) return "UNKNOWN VALUE EXCEPTION\n";
		return elements->get(index)->value;
	}
};
