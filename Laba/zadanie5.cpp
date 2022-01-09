#include <iostream>
#include <string>
#include <unordered_set>
#include <chrono>
#include "hashTable.h"

std::string string_generator() {

    char massiv_char[] = {"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    std::string str;

    int size = rand() % 10 + 1;

    for (int i = 0; i < size; i++) {
        str.push_back(massiv_char[rand() % 62]);
    }

    return str;
}

void comparison(int count) {

    HashTable<std::string> *table = new HashTable<std::string>();
    std::unordered_set<std::string> unorderedSet;

    std::cout << "count = " << count << "\n";

    auto start = std::chrono::system_clock::now();
	for (int i = 0; i < count; i++)
	{
		table->setData(string_generator());
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> sec_table = end - start;
    std::cout << "\tAdding to the HashTable took " << sec_table.count() << " seconds." << "\n";

    start = std::chrono::system_clock::now();
	for (int i = 0; i < count; i++)
	{
		unorderedSet.insert(string_generator());
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> sec_set = end - start;
    std::cout << "\tAdding to the UnorderedSet took " << sec_set.count() << " seconds." << "\n";

    delete table;
    unorderedSet.clear();
}

int main() {

    int min_count = 500;
    int max_count = 18500;
    int step = 2000;

    for (int i = min_count; i <= max_count; i = i + step) {
        comparison(i);
        std::cout << std::endl;
    }

    return 0;
}