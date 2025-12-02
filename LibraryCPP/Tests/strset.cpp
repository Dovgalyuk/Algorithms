#include <iostream>
#include <string>
#include "strset.h"

static std::string make_key(int x)
{
    return "key_" + std::to_string(x);
}

int main()
{
    StringSet* set = string_set_create();
    if (!set)
    {
        std::cout << "Failed to create StringSet\n";
        return 1;
    }

    if (!string_set_insert(set, "hello"))
    {
        std::cout << "Insert of 'hello' failed\n";
        string_set_delete(set);
        return 1;
    }

    if (!string_set_contains(set, "hello"))
    {
        std::cout << "Contains failed for 'hello'\n";
        string_set_delete(set);
        return 1;
    }

    if (string_set_insert(set, "hello"))
    {
        std::cout << "Duplicate insert of 'hello' should return false\n";
        string_set_delete(set);
        return 1;
    }

    if (!string_set_insert(set, "world"))
    {
        std::cout << "Insert of 'world' failed\n";
        string_set_delete(set);
        return 1;
    }

    if (!string_set_erase(set, "hello"))
    {
        std::cout << "Erase of 'hello' failed\n";
        string_set_delete(set);
        return 1;
    }

    if (string_set_contains(set, "hello"))
    {
        std::cout << "'hello' still in set after erase\n";
        string_set_delete(set);
        return 1;
    }

    if (!string_set_contains(set, "world"))
    {
        std::cout << "'world' missing after erase of 'hello'\n";
        string_set_delete(set);
        return 1;
    }

    if (string_set_erase(set, "no_such_key"))
    {
        std::cout << "Erase of non-existing key should return false\n";
        string_set_delete(set);
        return 1;
    }

    const int N = 200000;

    for (int i = 0; i < N; ++i)
    {
        std::string key = make_key(i);
        if (!string_set_insert(set, key))
        {
            std::cout << "Insert failed for key " << key << " at i = " << i << "\n";
            string_set_delete(set);
            return 1;
        }
    }

    for (int i = 0; i < N; i += 1000)
    {
        std::string key = make_key(i);
        if (!string_set_contains(set, key))
        {
            std::cout << "Contains failed for key " << key << " after bulk insert\n";
            string_set_delete(set);
            return 1;
        }
    }

    for (int i = 0; i < N; ++i)
    {
        std::string key = make_key(i);
        if (!string_set_erase(set, key))
        {
            std::cout << "Erase failed for key " << key << " at i = " << i << "\n";
            string_set_delete(set);
            return 1;
        }
    }

    for (int i = 0; i < N; i += 1000)
    {
        std::string key = make_key(i);
        if (string_set_contains(set, key))
        {
            std::cout << "Key " << key << " still in set after bulk erase\n";
            string_set_delete(set);
            return 1;
        }
    }

    std::cout << "StringSet tests passed\n";

    string_set_delete(set);
    return 0;
}
