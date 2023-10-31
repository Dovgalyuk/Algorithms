#include <iostream>
#include <string>
#include <stdio.h>
#include "array.h"
#include "hash.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");

	HashTable* table = new HashTable();

	size_t size_for_tests = 500000; //performance

	//add
	for (size_t i = 0; i < size_for_tests; i++) table->add(to_string(i), to_string(i));

	for (size_t i = 0; i < 100; i++)
	{
		auto result = table->find(to_string(i));
		if (!result.first || result.second != to_string(i)) {
			cout << "Searching or adding error\n";
		}
	}

	//remove
	for (size_t i = 0; i < size_for_tests; i++) { table->del(to_string(i)); }

	//check
	for (size_t i = 100; i < 120; i++)
	{
		auto result = table->find(to_string(i));
		if (result.first) {
			cout << "Search or insert error\n";
			return 1;
		}
	}

	delete table;
	return 0;
}