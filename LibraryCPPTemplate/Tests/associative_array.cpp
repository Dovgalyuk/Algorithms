#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include "map.h"

static unsigned long long comparisonCount = 0;

struct CountingKey
{
    long long value;

    CountingKey(long long initialValue = 0) : value(initialValue) {}

    bool operator<(const CountingKey &other) const
    {
        comparisonCount++;
        return value < other.value;
    }
};

bool check(bool condition, const char *message)
{
    if (!condition)
    {
        std::cout << "TEST FAILED: " << message << "\n";
        return false;
    }
    return true;
}

unsigned long long comparisonLimit(size_t size)
{
    return (unsigned long long)(3.0 * std::ceil(std::log2((double)size + 2.0)) + 3.0);
}

bool checkComplexity(unsigned long long comparisons, size_t size, const char *operation)
{
    unsigned long long limit = comparisonLimit(size);
    if (comparisons > limit)
    {
        std::cout << "COMPLEXITY FAILED: " << operation << ", N=" << size << ", comparisons=" << comparisons << ", limit=" << limit << "\n";
        return false;
    }
    return true;
}

std::vector<long long> makeOrder(size_t size, int pattern, std::mt19937 &generator)
{
    std::vector<long long> order;
    order.reserve(size);

    if (pattern == 0)
    {
        for (size_t i = 0 ; i < size ; i++) order.push_back((long long)i);
    }
    else if (pattern == 1)
    {
        for (size_t i = size ; i > 0 ; i--) order.push_back((long long)(i - 1));
    }
    else if (pattern == 2)
    {
        size_t left = 0;
        size_t right = size;
        while (left < right)
        {
            order.push_back((long long)left);
            left++;
            if (left < right)
            {
                right--;
                order.push_back((long long)right);
            }
        }
    }
    else
    {
        for (size_t i = 0 ; i < size ; i++) order.push_back((long long)i);
        std::shuffle(order.begin(), order.end(), generator);
    }

    return order;
}

bool testBasicOperations()
{
    AvlTreeMap<std::string, std::string> map;

    if (!check(map.empty() && map.size() == 0, "new map must be empty")) return false;
    if (!check(map.find("missing") == nullptr, "find in empty map")) return false;
    if (!check(!map.contains("missing"), "contains in empty map")) return false;
    if (!check(!map.erase("missing"), "erase in empty map")) return false;

    if (!check(map.insert("b", "2"), "insert b")) return false;
    if (!check(map.insert("a", "1"), "insert a")) return false;
    if (!check(map.insert("c", "3"), "insert c")) return false;
    if (!check(map.size() == 3 && !map.empty(), "size after insert")) return false;

    if (!check(map.find("a") && *map.find("a") == "1", "find existing key")) return false;
    if (!check(map.find("z") == nullptr, "find missing key")) return false;
    if (!check(map.contains("b"), "contains existing key")) return false;

    if (!check(!map.insert("b", "22"), "duplicate insert result")) return false;
    if (!check(map.size() == 3 && map.find("b") && *map.find("b") == "22", "duplicate insert must update value")) return false;

    if (!check(map.insert("", ""), "insert empty key and value")) return false;
    if (!check(map.find("") && *map.find("") == "", "find empty key and value")) return false;
    if (!check(map.erase(""), "erase empty key")) return false;

    if (!check(map.erase("a") && !map.erase("a"), "erase existing and repeated key")) return false;
    if (!check(map.size() == 2 && map.validate(), "basic map invariants")) return false;

    AvlTreeMap<std::string, std::string>::const_iterator current = map.begin();
    if (!check(current != map.end() && current->key == "b" && current->value == "22", "ascending iterator first item")) return false;
    current++;
    if (!check(current != map.end() && current->key == "c" && current->value == "3", "ascending iterator second item")) return false;
    current++;
    if (!check(current == map.end(), "ascending iterator end")) return false;

    if (!check(map.erase("b") && map.erase("c"), "erase remaining keys")) return false;
    if (!check(map.empty() && map.height() == 0 && map.validate(), "empty map after all erases")) return false;

    return true;
}

bool testLoadPattern(size_t testSize, int pattern, std::mt19937 &generator)
{
    std::vector<long long> order = makeOrder(testSize, pattern, generator);
    AvlTreeMap<CountingKey, int> map;
    unsigned long long worstInsert = 0;
    unsigned long long worstFind = 0;
    unsigned long long worstMissingFind = 0;
    unsigned long long worstUpdate = 0;
    unsigned long long worstErase = 0;

    for (size_t i = 0 ; i < testSize ; i++)
    {
        CountingKey key(order[i]);
        comparisonCount = 0;
        bool inserted = map.insert(key, (int)(order[i] * 3));
        unsigned long long usedComparisons = comparisonCount;

        if (!check(inserted, "load insert must add a new key")) return false;
        if (!checkComplexity(usedComparisons, map.size(), "insert")) return false;
        worstInsert = std::max(worstInsert, usedComparisons);
    }

    if (!check(map.size() == testSize && map.validate(), "tree invariants after load insertion")) return false;
    if (!check((double)map.height() <= 1.45 * std::log2((double)testSize + 2.0), "AVL height after load insertion")) return false;

    for (size_t i = 0 ; i < testSize ; i++)
    {
        CountingKey key((long long)i);
        comparisonCount = 0;
        const int *value = map.find(key);
        unsigned long long usedComparisons = comparisonCount;

        if (!check(value != nullptr && *value == (int)(i * 3), "load find existing key")) return false;
        if (!checkComplexity(usedComparisons, testSize, "find existing")) return false;
        worstFind = std::max(worstFind, usedComparisons);
    }

    for (size_t i = 0 ; i < testSize ; i++)
    {
        CountingKey key((long long)(testSize + i + 1));
        comparisonCount = 0;
        const int *value = map.find(key);
        unsigned long long usedComparisons = comparisonCount;

        if (!check(value == nullptr, "load find missing key")) return false;
        if (!checkComplexity(usedComparisons, testSize, "find missing")) return false;
        worstMissingFind = std::max(worstMissingFind, usedComparisons);
    }

    for (size_t i = 0 ; i < testSize ; i++)
    {
        CountingKey key((long long)i);
        comparisonCount = 0;
        bool inserted = map.insert(key, -(int)i);
        unsigned long long usedComparisons = comparisonCount;

        if (!check(!inserted, "duplicate load insert must not add a key")) return false;
        if (!checkComplexity(usedComparisons, testSize, "update")) return false;
        worstUpdate = std::max(worstUpdate, usedComparisons);
    }

    for (size_t i = 0 ; i < testSize ; i++)
    {
        CountingKey key((long long)i);
        const int *value = map.find(key);
        if (!check(value != nullptr && *value == -(int)i, "load update value")) return false;
    }

    for (size_t i = 0 ; i < testSize ; i++)
    {
        CountingKey key(order[testSize - i - 1]);
        comparisonCount = 0;
        bool erased = map.erase(key);
        unsigned long long usedComparisons = comparisonCount;

        if (!check(erased, "load erase existing key")) return false;
        if (!checkComplexity(usedComparisons, map.size() + 1, "erase")) return false;
        worstErase = std::max(worstErase, usedComparisons);
    }

    if (!check(map.empty() && map.size() == 0, "map must be empty after load erase")) return false;
    if (!check(map.height() == 0 && map.validate(), "tree invariants after load erase")) return false;

    return true;
}

bool testRandomOperations()
{
    const size_t operationCount = 4000;
    const long long keyRange = 1200;

    AvlTreeMap<CountingKey, int> map;
    std::map<long long, int> reference;
    std::mt19937 generator(20261104);
    std::uniform_int_distribution<long long> keyDistribution(0, keyRange - 1);
    std::uniform_int_distribution<int> operationDistribution(0, 2);
    std::uniform_int_distribution<int> valueDistribution(-100000, 100000);

    for (size_t i = 0 ; i < operationCount ; i++)
    {
        long long keyValue = keyDistribution(generator);
        int value = valueDistribution(generator);
        int operation = operationDistribution(generator);
        CountingKey key(keyValue);

        comparisonCount = 0;
        if (operation == 0)
        {
            bool expectedResult = reference.find(keyValue) == reference.end();
            bool actualResult = map.insert(key, value);
            reference[keyValue] = value;

            if (!check(actualResult == expectedResult, "random insert result")) return false;
            if (!checkComplexity(comparisonCount, map.size(), "random insert")) return false;
        }
        else if (operation == 1)
        {
            std::map<long long, int>::const_iterator expected = reference.find(keyValue);
            const int *actual = map.find(key);

            if (!check((actual != nullptr) == (expected != reference.end()), "random find presence")) return false;
            if (!check(actual == nullptr || *actual == expected->second, "random find value")) return false;
            if (!checkComplexity(comparisonCount, map.size(), "random find")) return false;
        }
        else
        {
            bool expectedResult = reference.erase(keyValue) != 0;
            bool actualResult = map.erase(key);

            if (!check(actualResult == expectedResult, "random erase result")) return false;
            if (!checkComplexity(comparisonCount, map.size() + 1, "random erase")) return false;
        }

        if ((i + 1) % 500 == 0)
        {
            if (!check(map.size() == reference.size() && map.validate(), "random workload invariants")) return false;
            if (!check((double)map.height() <= 1.45 * std::log2((double)map.size() + 2.0), "random workload AVL height")) return false;
        }
    }

    if (!check(map.size() == reference.size() && map.validate(), "final random workload invariants")) return false;

    AvlTreeMap<CountingKey, int>::const_iterator current = map.begin();
    std::map<long long, int>::const_iterator expected = reference.begin();

    while (current != map.end() && expected != reference.end())
    {
        if (!check(current->key.value == expected->first && current->value == expected->second, "random workload final contents")) return false;
        current++;
        expected++;
    }

    if (!check(current == map.end() && expected == reference.end(), "random workload traversal length")) return false;

    return true;
}


bool testIterators()
{
    typedef AvlTreeMap<std::string, std::string> StringMap;
    typedef AssociativeArray<std::string, std::string> Interface;

    StringMap map;
    const char *keys[] = {"d", "b", "f", "a", "c", "e", "g"};
    for (int i = 0 ; i < 7 ; i++) map.insert(keys[i], std::string(keys[i]) + std::string(keys[i]));

    std::string forward, backward;
    for (StringMap::const_iterator it = map.cbegin() ; it != map.cend() ; ++it) forward += it->key;
    for (StringMap::const_reverse_iterator it = map.rbegin() ; it != map.rend() ; ++it) backward += it->key;
    if (!check(forward == "abcdefg", "begin/end ascending order")) return false;
    if (!check(backward == "gfedcba", "rbegin/rend descending order")) return false;

    const Interface &base = map;
    std::string viaAscending, viaDescending;
    std::unique_ptr<Interface::Iterator> ascending = base.createIterator(Interface::Order::Ascending);
    for ( ; ascending->valid() ; ascending->next())
    {
        viaAscending += ascending->key();
        if (!check(ascending->value() == ascending->key() + ascending->key(), "createIterator value")) return false;
    }
    std::unique_ptr<Interface::Iterator> descending = base.createIterator(Interface::Order::Descending);
    for ( ; descending->valid() ; descending->next()) viaDescending += descending->key();
    if (!check(viaAscending == "abcdefg", "createIterator ascending")) return false;
    if (!check(viaDescending == "gfedcba", "createIterator descending")) return false;

    for (StringMap::iterator it = map.begin() ; it != map.end() ; ++it) it->value = "x";
    if (!check(map.find("a") && *map.find("a") == "x", "value changed through iterator")) return false;

    StringMap copy(map);
    copy.erase("a");
    copy.insert("z", "26");
    if (!check(map.size() == 7 && map.contains("a") && !map.contains("z"), "copy must be independent")) return false;
    if (!check(copy.size() == 7 && !copy.contains("a") && copy.contains("z") && copy.validate(), "copy contents")) return false;

    StringMap assigned;
    assigned.insert("q", "1");
    assigned = map;
    if (!check(assigned.size() == 7 && !assigned.contains("q") && assigned.validate(), "copy assignment")) return false;

    StringMap moved(std::move(copy));
    if (!check(moved.size() == 7 && copy.empty() && copy.begin() == copy.end(), "move constructor")) return false;

    map.clear();
    if (!check(map.empty() && map.begin() == map.end() && !map.createIterator()->valid(), "clear and empty iterators")) return false;
    if (!check(map.insert("k", "v") && map.size() == 1, "insert after clear")) return false;

    return true;
}

bool testLargeScale(bool quickMode)
{
    typedef AvlTreeMap<long long, long long> LargeMap;
    const long long count = quickMode ? 100000 : 1000000;
    LargeMap map;

    for (long long i = 0 ; i < count ; i++)
    {
        long long key = (i % 2 == 0) ? i / 2 : count - 1 - i / 2;
        if (!check(map.insert(key, key * 2), "large insert must add a new key")) return false;
    }

    if (!check(map.size() == (size_t)count && map.validate(), "large tree invariants")) return false;
    if (!check((double)map.height() <= 1.45 * std::log2((double)count + 2.0), "large AVL height")) return false;

    for (long long i = 0 ; i < count ; i += 50)
    {
        const long long *value = map.find(i);
        if (!check(value != nullptr && *value == i * 2, "large find existing key")) return false;
        if (!check(map.find(count + i) == nullptr, "large find missing key")) return false;
    }

    long long visited = 0;
    LargeMap::const_iterator it = map.cbegin();
    for ( ; it != map.cend() ; ++it)
    {
        if (!check(it->key == visited, "large iteration must be ascending without gaps")) return false;
        visited++;
    }
    if (!check(visited == count, "large iteration must visit every key")) return false;

    size_t erased = 0;
    for (long long i = 0 ; i < count ; i += 10)
    {
        if (!check(map.erase(i), "large erase existing key")) return false;
        erased++;
    }
    if (!check(map.size() == (size_t)count - erased && map.validate(), "large tree invariants after erase")) return false;
    if (!check(!map.contains(0) && map.contains(1), "large contents after erase")) return false;
    return true;
}

int main(int argc, char **argv)
{
    bool quickMode = false;
    std::string mode = "all";

    for (int i = 1 ; i < argc ; i++)
    {
        std::string argument = argv[i];
        if (argument == "--quick") quickMode = true;
        else if (argument == "basic" || argument == "iterators" || argument == "load" || argument == "random" || argument == "large" || argument == "all") mode = argument;
        else
        {
            std::cout << "Usage: AvlTest [--quick] [basic|iterators|load|random|large|all]\n";
            return 1;
        }
    }

    bool all = mode == "all";
    std::cout << "Starting AvlTreeMap tests (" << mode << ")\n";

    if (all || mode == "basic")
    {
        if (!testBasicOperations()) return 1;
        std::cout << "Basic operations: OK\n";
    }

    if (all || mode == "iterators")
    {
        if (!testIterators()) return 1;
        std::cout << "Iterators, copy and clear: OK\n";
    }

    if (all || mode == "load")
    {
        std::mt19937 generator(88172645u);
        const size_t testSizes[] = {256, 1024, 4096};
        const size_t quickTestSizes[] = {128, 512, 1024};
        const int patternCount = 4;

        for (int sizeIndex = 0 ; sizeIndex < 3 ; sizeIndex++)
        {
            size_t testSize = quickMode ? quickTestSizes[sizeIndex] : testSizes[sizeIndex];

            for (int pattern = 0 ; pattern < patternCount ; pattern++) if (!testLoadPattern(testSize, pattern, generator)) return 1;
        }
    }
    if (all || mode == "random")
    {
        if (!testRandomOperations()) return 1;
    }
    if (all || mode == "large")
    {
        if (!testLargeScale(quickMode)) return 1;
    }
    return 0;
}