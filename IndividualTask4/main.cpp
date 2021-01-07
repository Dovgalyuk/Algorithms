#include <iostream>
#include <ctime>
#include <set>
#include "set.h"

#define size 25000
#define stringSize 10

std::string randomString()
{
    std::string Str;
    Str.resize(stringSize);

    const char charSet[] ="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < stringSize; i++)
    {
        Str += charSet[rand() % (sizeof(charSet) - 1)];
    }
    return Str;
}

int main() 
{
    srand(time(NULL));
    clock_t start;
    clock_t end;

    std::string key[size];

    for (int i = 0; i < size; i++)
    {
        key[i] = randomString();
    }

    Set* set = set_create(key[0]);

    start = clock();          // start test my set

    for (int i = 1; i < size; i++)
    {
        set_insert(set, key[i]);
    }

    for (int i = 0; i < size; i++)
    {
        set_find(set, key[i]);
    }

    end = clock();
    
    set_delete(set);

    std::cout << "My crooked set did it for " << (double)(end - start) / CLOCKS_PER_SEC << " sec" << std::endl;


    std::set <std::string> Set;

    start = clock();

    for (int i = 1; i < size; i++)
    {
        Set.insert(key[i]);
    }

    for (int i = 0; i < size; i++)
    {
        Set.find(key[i]);
    }

    end = clock();

    std::cout << "Normal set did it for " << (double)(end - start) / CLOCKS_PER_SEC << " sec" << std::endl;;

    system("pause");
}

