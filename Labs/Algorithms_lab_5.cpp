#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include "HashTable.h"

using namespace std;

const char symbols[] = { "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

string random_word() {
	int size = rand() % 10 + 1;
	string str;
	for (int i = 0; i < size; i++) str.push_back(symbols[rand() % 62]);
	return str;
}

void execute(HashTable* table, int size) {
	unordered_map<string, string> map;

	chrono::system_clock::time_point start_table;
	chrono::system_clock::time_point table_end;
	chrono::system_clock::time_point start_map;
	chrono::system_clock::time_point map_end;

	chrono::duration<double> time_table;
	chrono::duration<double> time_map;

	string* random_value = new string[size];
	string* random_key = new string[size];

	for (int i = 0; i < size; i++) random_value[i] = random_word();
	for (int i = 0; i < size; i++) random_key[i] = random_word();

	start_table = chrono::system_clock::now();
	for (int i = 0; i < size; i++) add(random_key[i], random_value[i], table);
	table_end = chrono::system_clock::now();

	time_table = table_end - start_table;

	start_map = chrono::system_clock::now();
	for (int i = 0; i < size; i++) map[random_key[i]] = random_value[i];
	map_end = chrono::system_clock::now();

	time_map = map_end - start_map;

	cout << "Added " << size << " elements. My table is " << time_table.count() << ". Unordered_map is " << time_map.count() << ".\n";

	delete[] random_key;
	delete[] random_value;
}

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	HashTable* table = new HashTable();

	execute(table, 100);
	execute(table, 500);
	execute(table, 1000);
	execute(table, 5000);
	execute(table, 10000);
	execute(table, 50000);
	execute(table, 100000);
	execute(table, 200000);
	execute(table, 500000);
	execute(table, 800000);

	delete_table(table);

	return 0;
}