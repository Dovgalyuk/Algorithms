#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
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

size_t read_count(const string &text)
{
    check(!text.empty(), "Empty element count");
    size_t count = 0;
    for (char symbol : text)
    {
        check(symbol >= '0' && symbol <= '9', "Invalid element count");
        size_t digit = static_cast<size_t>(symbol - '0');
        check(count <= (numeric_limits<size_t>::max() - digit) / 10,
              "Element count is too large");
        count = count * 10 + digit;
    }
    check(count > 0, "Element count must be positive");
    return count;
}

int main(int argc, char *argv[])
{
    AVLTree *tree = nullptr;
    try
    {
        check(argc == 3, "Usage: Lab5CPPStress input.txt count");
        size_t expected = read_count(argv[2]);
        ifstream input(argv[1]);
        check(static_cast<bool>(input), "Cannot open input file");

        vector<string> values;
        string line;
        while (getline(input, line))
        {
            if (!line.empty() && line.back() == '\r')
                line.pop_back();
            values.push_back(line);
        }
        check(input.eof(), "Cannot read input file");
        check(values.size() == expected, "Unexpected number of input lines");

        tree = avl_create();
        auto begin = chrono::steady_clock::now();
        for (const string &value : values)
            check(avl_insert(tree, value), "Input contains duplicate values");
        double insert_ms = chrono::duration<double, milli>(
            chrono::steady_clock::now() - begin).count();

        check(avl_size(tree) == expected, "Invalid size after insertion");
        check(avl_check(tree), "Invalid AVL tree after insertion");
        int height = avl_height(tree);
        int levels = 0;
        for (size_t count = expected; count > 0; count /= 2)
            ++levels;
        check(height <= 2 * levels, "Tree is too tall");

        begin = chrono::steady_clock::now();
        for (const string &value : values)
            check(avl_find(tree, value), "Inserted value not found");
        double find_ms = chrono::duration<double, milli>(
            chrono::steady_clock::now() - begin).count();

        size_t visited = 0;
        string last;
        for (AVLIterator iterator = avl_begin(tree);
             avl_iterator_valid(iterator); avl_iterator_next(iterator))
        {
            const string &value = avl_iterator_get(iterator);
            check(visited == 0 || last < value, "Invalid iterator order");
            last = value;
            ++visited;
        }
        check(visited == expected, "Invalid iterator length");
        check(!avl_find(tree, last + "!"), "Missing value found");
        check(!avl_erase(tree, last + "!"), "Missing value removed");
        check(avl_size(tree) == expected, "Missing removal changed size");
        check(avl_check(tree), "Invalid AVL tree before removal");

        begin = chrono::steady_clock::now();
        for (size_t i = values.size(); i > 0; --i)
            check(avl_erase(tree, values[i - 1]), "Removal failed");
        double erase_ms = chrono::duration<double, milli>(
            chrono::steady_clock::now() - begin).count();

        check(avl_size(tree) == 0, "Tree is not empty after removal");
        check(avl_height(tree) == 0, "Invalid empty tree height");
        check(avl_check(tree), "Invalid AVL tree after removal");
        check(!avl_iterator_valid(avl_begin(tree)), "Empty iterator is valid");
        check(!avl_find(tree, values.front()), "Removed value found");

        avl_delete(tree);
        cout << "count=" << expected << " height=" << height << '\n';
        cout << fixed << setprecision(3)
             << "insert_ms=" << insert_ms << '\n'
             << "find_ms=" << find_ms << '\n'
             << "erase_ms=" << erase_ms << '\n';
        return 0;
    }
    catch (const exception &error)
    {
        avl_delete(tree);
        cerr << error.what() << '\n';
        return 1;
    }
}
