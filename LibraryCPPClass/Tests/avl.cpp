#include "avl.h"
#include <iostream>
#include <string>

void check(bool condition) 
{
    if(!condition) 
    {
        std::cout << "Test failed!" << std::endl;
        exit(1);
    }
}

void test_avl_basic() 
{
    AVL t;
    std::string value;

    t.add("key1", "value1");
    check(t.get("key1", value) && value == "value1");

    t.del("key1");
    check(!t.get("key1", value));

    std::cout << "AVL basic tests passed!" << std::endl;
}

void test_avl_1000_elements() 
{
    AVL t;
    std::string value;

    for(int i = 0; i < 1000; i++) 
    {
        t.add("key_" + std::to_string(i), "value_" + std::to_string(i));
    }

    for(int i = 0; i < 1000; i++) 
    {
        check(t.get("key_" + std::to_string(i), value));
        check(value == "value_" + std::to_string(i));
    }

    for(int i = 0; i < 1000; i++) 
    {
        t.del("key_" + std::to_string(i));
    }

    for(int i = 0; i < 1000; i++) 
    {
        check(!t.get("key_" + std::to_string(i), value));
    }

    std::cout << "1,000 elements test passed!" << std::endl;
}

void test_avl_10000_elements() 
{
    AVL t;
    std::string value;

    for(int i = 0; i < 10000; i++) 
    {
        t.add("key_" + std::to_string(i), "value_" + std::to_string(i));
    }

    for(int i = 0; i < 10000; i += 10) 
    {
        check(t.get("key_" + std::to_string(i), value));
        check(value == "value_" + std::to_string(i));
    }

    for(int i = 0; i < 10000; i++) 
    {
        t.del("key_" + std::to_string(i));
    }

    for(int i = 0; i < 100; i++) 
    {
        check(!t.get("key_" + std::to_string(i), value));
    }

    std::cout << "10,000 elements test passed!" << std::endl;
}

void test_avl_100000_elements() 
{
    AVL t;
    std::string value;

    for(int i = 0; i < 100000; i++) 
    {
        t.add("key_" + std::to_string(i), "val_" + std::to_string(i));
    }

    for(int i = 0; i < 100000; i += 100) 
    {
        check(t.get("key_" + std::to_string(i), value));
        check(value == "val_" + std::to_string(i));
    }

    for(int i = 0; i < 100000; i++) 
    {
        t.del("key_" + std::to_string(i));
    }

    for(int i = 0; i < 1000; i++) 
    {
        check(!t.get("key_" + std::to_string(i), value));
    }

    std::cout << "100,000 elements test passed!" << std::endl;
}

void test_avl_1_million() 
{
    AVL t;
    std::string value;

    for(int i = 0; i < 1000000; i++) 
    {
        t.add("key_" + std::to_string(i), "value_" + std::to_string(i));
    }

    for(int i = 0; i < 1000000; i++) 
    {
        check(t.get("key_" + std::to_string(i), value));
        check(value == "value_" + std::to_string(i));
    }

    for(int i = 0; i < 1000000; i++) 
    {
        t.del("key_" + std::to_string(i));
    }

    for(int i = 0; i < 100; i++) 
    {
        check(!t.get("key_" + std::to_string(i), value));
    }

    std::cout << "1,000,000 elements test passed!" << std::endl;
}

int main() 
{
    test_avl_basic();
    test_avl_1000_elements();
    test_avl_10000_elements();
    test_avl_100000_elements();
    test_avl_1_million();

    std::cout << "ALL TESTS PASSED!" << std::endl;
}