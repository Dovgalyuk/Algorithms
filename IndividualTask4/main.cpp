#include <iostream>
#include <ctime>
#include <set>
#include "set.h"

#define size 12500
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

    Set* myset = set_create(key[0]);

    start = clock();          // start test my set

    for (int i = 1; i < size; i++)
    {
        set_insert(myset, key[i]);
    }

    for (int i = 0; i < size; i++)
    {
        set_find(myset, key[i]);
    }

    end = clock();
    
    set_delete(myset);

    std::cout << "Test #1 mySet: " << (double)(end - start) / CLOCKS_PER_SEC << " sec" << std::endl;


    std::set <std::string> normalSet;

    start = clock();

    for (int i = 1; i < size; i++)
    {
        normalSet.insert(key[i]);
    }

    for (int i = 0; i < size; i++)
    {
        normalSet.find(key[i]);
    }

    end = clock();

    std::cout << "Test #1 std::set :" << (double)(end - start) / CLOCKS_PER_SEC << " sec" << std::endl;;

    std::cout << "Checking for throttling: " << std::endl;

    myset = set_create(key[0]);

    start = clock();          // start test my set

    for (int i = 1; i < size; i++)
    {
        set_insert(myset, key[i]);
    }

    for (int i = 0; i < size; i++)
    {
        set_find(myset, key[i]);
    }

    end = clock();

    set_delete(myset);

    std::cout << "Test #2 mySet: " << (double)(end - start) / CLOCKS_PER_SEC << " sec" << std::endl;


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

    std::cout << "Test #2 std::set :" << (double)(end - start) / CLOCKS_PER_SEC << " sec" << std::endl;;

    system("pause");
}

