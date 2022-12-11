#include <iostream>
#include "../LibraryCPPTemaplate/array.h"

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

int FirstHashFunction(string key, int capacity);
int SecondHashFunction(string key, int capacity);

void add(string key, string value, HashTable* table);
void del(string key, HashTable* table);
string find(string key, HashTable* table);
void resize(HashTable* table);
int find_index(string key, HashTable* table);
bool compare_strings(string first, string second);
bool check_capacity(int size, int capacity);
