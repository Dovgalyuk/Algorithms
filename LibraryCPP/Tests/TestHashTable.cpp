//#include <iostream>
//#include "HashTable.h"
//#include <string>
//#include <stdio.h>
//
//using namespace std;
//
//int main() {
//	setlocale(LC_ALL, "rus");
//
//	HashTable* table = new HashTable();
//
//	int size_for_tests = 500;
//
//	//adding elements
//	for (size_t i = 0; i < size_for_tests; i++) { add(to_string(i), to_string(i), table); }
//
//	for (size_t i = 100; i < 120; i++){
//		if (find(to_string(i), table) != to_string(i)) {
//			cout << "Searching or finding error\n";
//		}
//	}
//
//	//removing elements
//	for (size_t i = 0; i < size_for_tests; i++) { del(to_string(i), table); }
//
//	//check
//	for (size_t i = 100; i < 200; i++) {
//		if (find(to_string(i), table) != "UNKNOWN VALUE EXCEPTION\n") {
//			cout << "Search or insert error\n";
//			return 1;
//		}
//	}
//
//	return 0;
//}