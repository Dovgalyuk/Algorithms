#include "radix_map.h"
using namespace std;

int main()
{
    RadixMap values;
    values.insert("", "empty");
    values.insert("banana", "yellow");
    values.insert("apple", "red");
    values.insert("banana", "green");

    const string *empty = values.find("");
    const string *apple = values.find("apple");
    const string *banana = values.find("banana");
    if (empty == nullptr || *empty != "empty"
        || apple == nullptr || *apple != "red"
        || banana == nullptr || *banana != "green"
        || values.find("orange") != nullptr)
        return 1;

    RadixMap::Entries expected;
    expected.push_back(make_pair("", "empty"));
    expected.push_back(make_pair("apple", "red"));
    expected.push_back(make_pair("banana", "green"));
    if (values.entries() != expected)
        return 1;

    size_t position = 0;
    for (RadixMap::const_iterator it = values.begin(); it != values.end(); ++it, ++position)
        if (position >= expected.size() || *it != expected[position])
            return 1;
    if (position != expected.size())
        return 1;

    if (values.erase("orange") || !values.erase("apple")
        || values.find("apple") != nullptr || values.find("banana") == nullptr
        || !values.erase("banana") || !values.erase("")
        || !values.entries().empty())
        return 1;

    return 0;
}
