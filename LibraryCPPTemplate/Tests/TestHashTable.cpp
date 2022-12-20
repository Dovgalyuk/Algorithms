#include <iostream>
#include <string>
#include <stdio.h>
#include "array.h"
#include "HashTable.h"

using namespace std;

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");

	HashTable* table = new HashTable();

	int size_for_tests = 1000000;
	int counter = 0;

	//adding elements
	for (size_t i = 0; i < size_for_tests; i++) table->add(to_string(i), to_string(i));

	for (size_t i = 0; i < 100; i++) if (table->find(to_string(i)) != to_string(i)) cout << "Searching or adding error\n";

	//removing elements
	for (size_t i = 0; i < size_for_tests; i++) { table->del(to_string(i)); }

	//check
	for (size_t i = 100; i < 120; i++)if (table->find(to_string(i)) != "UNKNOWN VALUE EXCEPTION\n") { cout << "Search or insert error\n"; return 1; }

	return 0;
}
