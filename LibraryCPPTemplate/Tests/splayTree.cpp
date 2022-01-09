#include <iostream>
#include <ctime>
#include <string>
#include "splayTree.h"

int main()
{
    SplayTree test;
    if (!test.empty())
    {
        std::cout << "error, splay tree is empty";
    }
    for (int i = 0; i < 10000000; ++i)
    {
        std::string i2 = std::to_string(i);
        test.insert(i2);
    }
    if (!test.findNode("100"))
    {
        std::cout << "error, number not found";
    }
    test.remove("100");
    if (test.findNode("100"))
    {
        std::cout << "error, deletion did not happen";
    }
    test.insert("100");
    test.findNode("5045");
    test.findNode("215626");
    test.findNode("42151");
    test.findNode("111111");
    test.findNode("977777");

    for (int i = 0; i < 5; ++i)
    {
        std::string i2 = std::to_string(i);
        test.remove(i2);
        auto *node = test.findNode(i2);
        if (node)
        {
            std::cout << "Removing from an associative array does not work correctly.\n";
            return 1;
        }
    }
    return 0;
}