#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");

	HashTable* table = new HashTable();

	int size_for_tests = 1000000;

	//adding elements
	for (size_t i = 0; i < size_for_tests; i++) add(to_string(i), to_string(i), table);

	for (size_t i = 0; i < 100; i++) {
		if (find(to_string(i), table) != to_string(i)) cout << "Searching or adding error\n";
	}

	//removing elements
	for (size_t i = 0; i < size_for_tests; i++) { del(to_string(i), table); }

	//check
	for (size_t i = 100; i < 120; i++) {
		if (find(to_string(i), table) != "UNKNOWN VALUE EXCEPTION\n") {
			cout << "Search or insert error\n";
			return 1;
		}
	}
	
	delete_table(table);

	return 0;
}
