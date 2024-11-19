#include <iostream>
#include <cassert>
#include "hash_table.h"

void testInsertAndGet() {
    HashTable hashTable;
    hashTable.insert("key1", "value1");
    hashTable.insert("key2", "value2");
    hashTable.insert("key3", "value3");
    hashTable.insert("key4", "value4");
    hashTable.insert("key5", "value5");

    assert(hashTable.get("key1") == "value1");
    assert(hashTable.get("key2") == "value2");
    assert(hashTable.get("key3") == "value3");
    assert(hashTable.get("key4") == "value4");
    assert(hashTable.get("key5") == "value5");
}

void testUpdateValue() {
    HashTable hashTable;
    hashTable.insert("key1", "value1");
    hashTable.insert("key2", "value2");
    hashTable.insert("key3", "value3");

    hashTable.set("key1", "new_value1");
    hashTable.set("key2", "new_value2");

    assert(hashTable.get("key1") == "new_value1");
    assert(hashTable.get("key2") == "new_value2");
    assert(hashTable.get("key3") == "value3");
}

void testCheckKeyExists() {
    HashTable hashTable;
    hashTable.insert("key1", "value1");
    hashTable.insert("key2", "value2");
    hashTable.insert("key3", "value3");
    hashTable.insert("key4", "value4");
    hashTable.insert("key5", "value5");

    assert(hashTable.check_key("key1") == true);
    assert(hashTable.check_key("key3") == true);
    assert(hashTable.check_key("key5") == true);
    assert(hashTable.check_key("key6") == false);
}

void testRemoveKey() {
    HashTable hashTable;
    hashTable.insert("key1", "value1");
    hashTable.insert("key2", "value2");
    hashTable.insert("key3", "value3");
    hashTable.insert("key4", "value4");
    hashTable.insert("key5", "value5");

    hashTable.remove("key3");
    assert(hashTable.check_key("key3") == false);
    assert(hashTable.get("key1") == "value1");
    assert(hashTable.get("key2") == "value2");
    assert(hashTable.get("key4") == "value4");
    assert(hashTable.get("key5") == "value5");
}

void testInsertAndRemoveMillion() {
    HashTable hashTable;

    for (int i = 1; i <= 1000000; ++i) {
        hashTable.insert("key" + std::to_string(i), "value" + std::to_string(i));
    }

    for (int i = 1; i <= 1000000; ++i) {
        assert(hashTable.get("key" + std::to_string(i)) == "value" + std::to_string(i));
    }

    for (int i = 1; i <= 1000000; ++i) {
        hashTable.remove("key" + std::to_string(i));
    }

    for (int i = 1; i <= 1000000; ++i) {
        assert(hashTable.check_key("key" + std::to_string(i)) == false);
    }
}

int main() {
    testInsertAndGet();
    testUpdateValue();
    testCheckKeyExists();
    testRemoveKey();
    testInsertAndRemoveMillion();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
