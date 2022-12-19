#pragma once
#include <iostream>
#include "../LibraryCPPTemplate/array.h"

using namespace std;

struct Element {
	Element();
	Element(string key, string value, bool deleted);
	string key, value;
	bool deleted;
};
struct HashTable {
	Array<Element>* elements;
	int capacity;
	int elements_size;
	int cnt_del;
	HashTable();
	~HashTable();
};

//-------------------- Hash Functions -------------------//
int FirstHashFunction(const string& key, int capacity);
int SecondHashFunction(const string& key, int capacity);
//-------------------------------------------------------//

//---------------- Functions for solution ---------------//
int algorithm(string key, HashTable* table, Array<Element>* arr, bool &not_found);
void add(string key, string value, HashTable* table);
void resize(HashTable* table);
void del(string key, HashTable* table);
int find_index(string key, HashTable* table);
string find(string key, HashTable* table);
bool compare_strings(string first, string second);
bool check_capacity(int size, int capacity);
//-------------------------------------------------------//

void delete_table(HashTable* table);
