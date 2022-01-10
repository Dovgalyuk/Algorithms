#include <iostream>
#include <string>
#include "hashTable.h"

int main() {

    HashTable<std::string> *table = new HashTable<std::string>();

    int load_data = 1000000;

    for (int i = 0; i < load_data; i++) {
        table->setData(std::to_string(i));
    }

    for (int i = 150; i < 250; i++) {
        if (!table->findData(std::to_string(i))) {
            std::cout << "Find or set error\n";
            return 1;
        }
    }

    if (table->findData(std::to_string(1000000))) {
        std::cout << "Not value - 1000000\n";
        return 1;
    }

    for (int i = 0; i < load_data; i++) {
        table->deleteData(std::to_string(i));
    }

    for (int i = 0; i < load_data; i++) {
        if (table->findData(std::to_string(i))) {
            std::cout << "Delete error\n";
            return 1;
        }
    }

    std::cout << "OK\n";

    delete table;
}