#include <iostream>
#include <set>
#include <chrono>
#include "splayTree.h"


int main() {
    int n = 100;
    srand(time(0));

    
    std::cout<<"splayTree:\n";
    for (int j = 0; j < 6; j++) {
        SplayTree test1;   
        auto start = std::chrono::system_clock::now();
        for (int i = 0; i < n; ++i) {
        std::string i2 = std::to_string(i);
        test1.insert(i2);
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double, std::micro> result = end - start;
        start = std::chrono::system_clock::now();
        for (int i = 0; i < 10; i++) {
            int rand = rand % n;
            std::string randStr = std::to_string(rand);
            test1.findNode(randStr);
        }
        end = std::chrono::system_clock::now();
        std::chrono::duration<double, std::micro> result2 = end - start;

        std::cout<<"data capacity: " << n;
        std::cout << " ,time(insert) :" << result.count()<<" microseconds, ";
        std::cout << "time(find) :" << result2.count()<<" microseconds\n ";

        n *=10;
    }
    n = 100;
    std::cout<<"std::set:\n";
    for (int j = 0; j < 6; j++) {
        std::set <std::string> test2;   
        auto start = std::chrono::system_clock::now();
        for (int i = 0; i < n; ++i) {
        std::string i2 = std::to_string(i);
        test2.insert(i2);   
        }
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double, std::micro> result3 = end - start;
        start = std::chrono::system_clock::now();
        for (int i = 0; i < 10; i++) {
            int rand = rand % n;
            std::string randStr = std::to_string(rand);
            test2.find(randStr);
        }
        end = std::chrono::system_clock::now();
        std::chrono::duration<double, std::micro> result4 = end - start;
        std::cout<<"data capacity: " << n;
        std::cout << " ,time(insert) :" << result3.count()<<" microseconds, ";
        std::cout << "time(find) :" << result4.count()<<" microseconds\n ";

        n *=10;
    }
    
    return 0;
}