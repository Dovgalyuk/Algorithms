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
    std::string *massiv_str = new std::string[count];

    for (int i = 0; i < count; i++) {
        massiv_str[i] = string_generator();
    }

    std::cout << "count = " << count << "\n";

    auto start = std::chrono::system_clock::now();
	for (int i = 0; i < count; i++)
	{
		table->setData(massiv_str[i]);
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> sec_table = end - start;
    std::cout << "\tAdding to the HashTable took " << sec_table.count() << " seconds." << "\n";

    start = std::chrono::system_clock::now();
	for (int i = 0; i < count; i++)
	{
		unorderedSet.insert(massiv_str[i]);
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> sec_set = end - start;
    std::cout << "\tAdding to the UnorderedSet took " << sec_set.count() << " seconds." << "\n";

    std::cout << std::endl;

    delete table;
    unorderedSet.clear();
    delete[] massiv_str;
}

int main() {

    comparison(500);

    comparison(1000);

    comparison(10000);

    comparison(24000);
    
    comparison(50000);

    comparison(100000);

    comparison(200000);

    comparison(500000);

    comparison(1000000);

    return 0;
}