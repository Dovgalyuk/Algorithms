#include <iostream>
#include <string>
#include "map.h"

int main()
{
    Map map;

    map.insert("key1", "value1");
    map.insert("key2", "value2");
    map.insert("key3", "value3");

    std::string value;
    if (!map.find("key1", value) || value != "value1")
    {
        std::cout << "Invalid find for key1\n";
        return 1;
    }

    if (!map.find("key2", value) || value != "value2")
    {
        std::cout << "Invalid find for key2\n";
        return 1;
    }

    if (!map.find("key3", value) || value != "value3")
    {
        std::cout << "Invalid find for key3\n";
        return 1;
    }

    if (map.size() != 3)
    {
        std::cout << "Invalid size after insertion\n";
        return 1;
    }

    map = map;

    if (!map.find("key1", value) || value != "value1")
    {
        std::cout << "Invalid find after self-assignment\n";
        return 1;
    }

    if (!map.remove("key2"))
    {
        std::cout << "Failed to remove key2\n";
        return 1;
    }

    if (map.find("key2", value))
    {
        std::cout << "Key2 found after removal\n";
        return 1;
    }

    if (map.size() != 2)
    {
        std::cout << "Invalid size after removal\n";
        return 1;
    }

    map.insert("key1", "new_value1");
    if (!map.find("key1", value) || value != "new_value1")
    {
        std::cout << "Invalid value after update\n";
        return 1;
    }

    if (map.find("nonexistent", value))
    {
        std::cout << "Found nonexistent key\n";
        return 1;
    }

    map.clear();
    if (!map.empty())
    {
        std::cout << "Map not empty after clear\n";
        return 1;
    }

    if (map.size() != 0)
    {
        std::cout << "Invalid size after clear\n";
        return 1;
    }

    Map map2;
    map2.insert("a", "1");
    map2.insert("b", "2");
    
    Map map3 = map2;
    
    if (!map3.find("a", value) || value != "1")
    {
        std::cout << "Invalid copy constructor\n";
        return 1;
    }

    if (!map3.find("b", value) || value != "2")
    {
        std::cout << "Invalid copy constructor\n";
        return 1;
    }

    if (!map2.find("a", value) || value != "1")
    {
        std::cout << "Original modified after copy\n";
        return 1;
    }

    Map perfMap;

    for (int i = 1; i <= 1000000; ++i)
    {
        std::string key = "key_" + std::to_string(i);
        std::string val = "value_" + std::to_string(i);
        perfMap.insert(key, val);
    }

    if (perfMap.size() != 1000000)
    {
        std::cout << "Invalid size after mass insertion: " << perfMap.size() << "\n";
        return 1;
    }

    long long sum = 0;
    for (int i = 1; i <= 1000000; i += 10)
    {
        std::string key = "key_" + std::to_string(i);
        std::string found_value;
        if (perfMap.find(key, found_value))
        {
            sum += i;
        }
    }

    for (int i = 1; i <= 500000; ++i)
    {
        std::string key = "key_" + std::to_string(i);
        perfMap.remove(key);
    }

    if (perfMap.size() != 500000)
    {
        std::cout << "Invalid size after mass removal: " << perfMap.size() << "\n";
        return 1;
    }

    Map copy = perfMap;

    if (copy.size() != 500000)
    {
        std::cout << "Invalid copy size: " << copy.size() << "\n";
        return 1;
    }

    std::string test_value;
    if (!copy.find("key_600000", test_value) || test_value != "value_600000")
    {
        std::cout << "Invalid copy content\n";
        return 1;
    }

    if (!perfMap.find("key_600000", test_value) || test_value != "value_600000")
    {
        std::cout << "Original modified after copy\n";
        return 1;
    }

    for (int i = 1; i <= 500000; ++i)
    {
        std::string key = "key_" + std::to_string(i);
        if (perfMap.find(key, test_value))
        {
            std::cout << "Found removed key: " << key << "\n";
            return 1;
        }
    }
}