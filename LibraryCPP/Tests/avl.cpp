#include <iostream>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include "avl.h"

using namespace std;

void check(bool condition, const char *message)
{
    if (!condition)
        throw runtime_error(message);
}

string make_value(int number)
{
    string value = to_string(number);
    return string(8 - value.size(), '0') + value;
}

void check_tree(const AVLTree *tree, const set<string> &expected)
{
    check(avl_check(tree), "Invalid AVL tree");
    check(avl_size(tree) == expected.size(), "Invalid size");

    int levels = 0;
    for (size_t count = expected.size(); count > 0; count /= 2)
        ++levels;
    check(avl_height(tree) <= 2 * levels, "Tree is too tall");

    AVLIterator iterator = avl_begin(tree);
    for (const string &value : expected)
    {
        check(avl_iterator_valid(iterator), "Iterator ended too early");
        check(avl_iterator_get(iterator) == value, "Invalid iterator order");
        avl_iterator_next(iterator);
    }
    check(!avl_iterator_valid(iterator), "Iterator contains extra values");
    avl_iterator_next(iterator);
    check(!avl_iterator_valid(iterator), "End iterator changed");
}

void test_empty(AVLTree *tree)
{
    check_tree(tree, {});
    check(avl_height(tree) == 0, "Invalid empty height");
    check(!avl_find(tree, "missing"), "Found value in empty tree");
    check(!avl_erase(tree, "missing"), "Removed value from empty tree");

    AVLIterator iterator = avl_begin(tree);
    bool failed = false;
    try
    {
        avl_iterator_get(iterator);
    }
    catch (const out_of_range &)
    {
        failed = true;
    }
    check(failed, "Reading end iterator must fail");

    check(avl_size(nullptr) == 0, "Invalid null size");
    check(avl_height(nullptr) == 0, "Invalid null height");
    check(!avl_find(nullptr, "value"), "Found value in null tree");
    check(!avl_insert(nullptr, "value"), "Inserted into null tree");
    check(!avl_erase(nullptr, "value"), "Removed from null tree");
    check(!avl_iterator_valid(avl_begin(nullptr)), "Invalid null iterator");
    avl_delete(nullptr);
}

void test_strings(AVLTree *tree)
{
    vector<string> values = {
        "", "a", "A", "aa", "ab", "z", "two words", "строка", string(4096, 'x')
    };
    set<string> expected;

    for (const string &value : values)
    {
        check(avl_insert(tree, value), "Insertion failed");
        expected.insert(value);
        check(avl_find(tree, value), "Inserted value not found");
        check(!avl_insert(tree, value), "Duplicate inserted");
        check_tree(tree, expected);
    }

    check(!avl_find(tree, "absent"), "Missing value found");
    check(!avl_erase(tree, "absent"), "Missing value removed");
    check_tree(tree, expected);

    for (const string &value : values)
    {
        check(avl_erase(tree, value), "Removal failed");
        expected.erase(value);
        check(!avl_find(tree, value), "Removed value still found");
        check(!avl_erase(tree, value), "Value removed twice");
        check_tree(tree, expected);
    }
}

void test_rotations(AVLTree *tree)
{
    vector<vector<string>> cases = {
        {"30", "20", "10"},
        {"10", "20", "30"},
        {"30", "10", "20"},
        {"10", "30", "20"}
    };

    for (const vector<string> &values : cases)
    {
        set<string> expected;
        for (const string &value : values)
        {
            check(avl_insert(tree, value), "Rotation insertion failed");
            expected.insert(value);
            check_tree(tree, expected);
        }
        check(avl_height(tree) == 2, "Rotation did not balance tree");

        for (const string &value : vector<string>{"20", "10", "30"})
        {
            check(avl_erase(tree, value), "Rotation removal failed");
            expected.erase(value);
            check_tree(tree, expected);
        }
    }
}

void test_removal(AVLTree *tree)
{
    vector<vector<string>> cases = {
        {"20"},
        {"20", "10"},
        {"20", "10", "30"},
        {"40", "20", "60", "10", "30", "50", "70", "55"},
        {"50", "30", "70", "20", "40", "60", "80", "10", "25", "35", "45"}
    };

    for (const vector<string> &values : cases)
    {
        set<string> expected;
        for (const string &value : values)
        {
            check(avl_insert(tree, value), "Removal setup failed");
            expected.insert(value);
        }
        check_tree(tree, expected);

        for (const string &value : values)
        {
            check(avl_erase(tree, value), "Removal case failed");
            expected.erase(value);
            check(!avl_find(tree, value), "Erased value still exists");
            check_tree(tree, expected);
        }
    }
}

void test_random(AVLTree *tree)
{
    mt19937 generator(5093);
    set<string> expected;

    for (int i = 0; i < 30000; ++i)
    {
        string value = make_value(static_cast<int>(generator() % 6000));
        unsigned int operation = generator() % 3;

        if (operation == 0)
            check(avl_insert(tree, value) == expected.insert(value).second,
                  "Random insertion differs from set");
        else if (operation == 1)
            check(avl_erase(tree, value) == (expected.erase(value) != 0),
                  "Random removal differs from set");
        else
            check(avl_find(tree, value) == (expected.find(value) != expected.end()),
                  "Random search differs from set");

        if (i % 251 == 0)
            check_tree(tree, expected);
    }
    check_tree(tree, expected);

    while (!expected.empty())
    {
        string value = *expected.begin();
        check(avl_erase(tree, value), "Random cleanup failed");
        expected.erase(value);
        if (expected.size() % 251 == 0)
            check_tree(tree, expected);
    }
    check_tree(tree, expected);
}

void test_ordered(AVLTree *tree, bool reverse)
{
    const int count = 25000;
    set<string> expected;

    for (int i = 0; i < count; ++i)
    {
        string value = make_value(reverse ? count - i - 1 : i);
        check(avl_insert(tree, value), "Ordered insertion failed");
        expected.insert(value);
        if ((i + 1) % 5000 == 0)
            check_tree(tree, expected);
    }

    for (int i = 0; i < count; ++i)
        check(avl_find(tree, make_value(i)), "Ordered search failed");
    check(!avl_find(tree, make_value(count)), "Missing ordered value found");

    for (int i = 0; i < count; ++i)
    {
        string value = make_value(reverse ? i : count - i - 1);
        check(avl_erase(tree, value), "Ordered removal failed");
        expected.erase(value);
        if ((i + 1) % 5000 == 0)
            check_tree(tree, expected);
    }
    check_tree(tree, expected);
}

int main()
{
    AVLTree *tree = nullptr;
    try
    {
        tree = avl_create();
        test_empty(tree);
        test_strings(tree);
        test_rotations(tree);
        test_removal(tree);
        test_random(tree);
        test_ordered(tree, false);
        test_ordered(tree, true);
        for (int i = 0; i < 1000; ++i)
            check(avl_insert(tree, make_value(i)), "Final insertion failed");
        avl_delete(tree);
        cout << "AVL tests passed\n";
        return 0;
    }
    catch (const exception &error)
    {
        avl_delete(tree);
        cerr << error.what() << '\n';
        return 1;
    }
}
