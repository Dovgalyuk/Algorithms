#include "Map.h"
#include <iostream>
#include <cassert>
#include <chrono>
using namespace std;


void basicTests() {
    AssociativeArray arr;

    arr.insert("key1", "value1");
    arr.insert("key2", "value2");
    arr.insert("key3", "value3");
    arr.insert("key4", "value4");
    arr.insert("key5", "value5");

   
    if (arr.find("key1")!= "value1") {
        throw std::runtime_error("value not found");
    }
    if (arr.find("key2")!= "value2") {
        throw std::runtime_error("value not found");
    }
    if (arr.find("key3")!= "value3") {
        throw std::runtime_error("value not found");
    }
    if (arr.find("key4")!= "value4") {
        throw std::runtime_error("value not found");

    }
    if (arr.find("key5")!= "value5") {
        throw std::runtime_error("value not found");

    }
    if (!arr.find("key6").empty()) {
        throw std::runtime_error("incorrect search");

    }
    if (!arr.find("key7").empty()) {
        throw std::runtime_error("incorrect search");

    }

    arr.insert("key1", "new_value1");
    if ((arr.find("key1") != "new_value1")) {
        throw std::runtime_error(" new value not found");
    }
    arr.insert("key2", "new_value2");
    if ((arr.find("key2") != "new_value2")) {
        throw std::runtime_error("new value not found");
    }

    
    arr.remove("key1");
    arr.remove("key2");
    arr.remove("key3");
    arr.remove("key4");
    arr.remove("key5");
    if (arr.countNodes() != 0) {
        throw std::runtime_error("deletion error");
    }
   
   
}

void loadTest() {
    AssociativeArray arr;
    const int numElements = 10000000;

    
    for (int i = 0; i < numElements; ++i) {
        arr.insert("key" + std::to_string(i), "value" + std::to_string(i));
    }

    
    for (int i = 0; i < numElements; ++i) {
        if ((arr.find("key" + std::to_string(i)) != "value" + std::to_string(i))) {
            throw std::runtime_error("deletion error");
        }
    }


    for (int i = 0; i < numElements; ++i) {
        arr.remove("key" + std::to_string(i));
    }

    
    if (arr.countNodes() != 0){

        throw std::runtime_error("Tests error");
    }

   
}

int main() {
    try {
        basicTests();
        loadTest();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
