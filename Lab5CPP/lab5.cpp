#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <algorithm>
#include <cassert>
#include "avltree.h"

using namespace std;
using namespace std::chrono;

string generateRandomString(size_t length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    static mt19937 rng(random_device{}());
    static uniform_int_distribution<size_t> dist(0, sizeof(alphanum) - 2);

    string result;
    result.reserve(length);

    for (size_t i = 0; i < length; ++i) {
        result += alphanum[dist(rng)];
    }

    return result;
}

void generateInputFile(const string& filename, size_t count) {
    ofstream file(filename);
    if (!file) {
        cerr << "Cannot create file: " << filename << endl;
        return;
    }

    cout << "Generating " << count << " random strings to " << filename << endl;

    for (size_t i = 0; i < count; ++i) {

        size_t length = 5 + (i % 16);
        file << generateRandomString(length) << endl;
    }

    file.close();
    cout << "File generated: " << filename << endl;
}

void testBasicFunctionality() {
    cout << "\n=== Testing Basic Functionality ===" << endl;

    AVLTree tree;

    assert(tree.insert("apple"));
    assert(tree.insert("banana"));
    assert(tree.insert("cherry"));
    assert(tree.size() == 3);

    assert(tree.contains("apple"));
    assert(tree.contains("banana"));
    assert(!tree.contains("grape"));

    assert(tree.remove("banana"));
    assert(!tree.contains("banana"));
    assert(tree.size() == 2);

    assert(tree.insert("apple"));
    assert(tree.size() == 3);

    assert(tree.isBalanced());
    assert(tree.isBST());

    cout << "All basic tests passed!" << endl;
}

void stressTest(size_t numElements) {
    cout << "\n=== Stress Test with " << numElements << " elements ===" << endl;

    AVLTree tree;
    set<string> stdSet;
    vector<string> elements;

    for (size_t i = 0; i < numElements; ++i) {
        elements.push_back("element_" + to_string(i));
    }

    shuffle(elements.begin(), elements.end(), mt19937(random_device{}()));

    auto start = high_resolution_clock::now();
    for (const auto& elem : elements) {
        tree.insert(elem);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "AVLTree insertion time: " << duration.count() << " ms" << endl;

    if (!tree.isBalanced()) {
        cerr << "ERROR: Tree is not balanced after insertions!" << endl;
    }

    if (!tree.isBST()) {
        cerr << "ERROR: Tree is not a valid BST!" << endl;
    }

    start = high_resolution_clock::now();
    for (const auto& elem : elements) {
        if (!tree.contains(elem)) {
            cerr << "ERROR: Element not found: " << elem << endl;
        }
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "AVLTree search time: " << duration.count() << " ms" << endl;

    reverse(elements.begin(), elements.end());
    start = high_resolution_clock::now();
    for (const auto& elem : elements) {
        tree.remove(elem);
    }
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "AVLTree deletion time: " << duration.count() << " ms" << endl;

    if (!tree.empty()) {
        cerr << "ERROR: Tree should be empty after deletion!" << endl;
    }

    cout << "Stress test completed!" << endl;
}

void compareWithStdSet(const string& filename) {
    cout << "\n=== Comparing AVLTree with std::set ===" << endl;

    ifstream file(filename);
    if (!file) {
        cerr << "Cannot open file: " << filename << endl;
        return;
    }

    vector<string> lines;
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    file.close();

    cout << "Loaded " << lines.size() << " lines from " << filename << endl;

    AVLTree avlTree;
    auto start = high_resolution_clock::now();
    for (const auto& l : lines) {
        avlTree.insert(l);
    }
    auto end = high_resolution_clock::now();
    auto avlTime = duration_cast<microseconds>(end - start);

    set<string> stdSet;
    start = high_resolution_clock::now();
    for (const auto& l : lines) {
        stdSet.insert(l);
    }
    end = high_resolution_clock::now();
    auto setTime = duration_cast<microseconds>(end - start);

    cout << "AVLTree insertion time: " << avlTime.count() << " microseconds" << endl;
    cout << "std::set insertion time: " << setTime.count() << " microseconds" << endl;
    cout << "Ratio (AVL/std::set): " << (double)avlTime.count() / setTime.count() << endl;

    auto avlElements = avlTree.getAllElements();
    vector<string> setElements(stdSet.begin(), stdSet.end());

    sort(avlElements.begin(), avlElements.end());

    if (avlElements == setElements) {
        cout << "Both containers have identical elements!" << endl;
    }
    else {
        cerr << "ERROR: Elements mismatch between containers!" << endl;
    }
}

void performanceComparison() {
    cout << "\n=== Performance Comparison (CSV format) ===" << endl;
    cout << "Size,AVLTree(us),std::set(us),Ratio" << endl;

    vector<size_t> sizes = { 100, 500, 1000, 5000, 10000, 20000, 50000 };

    for (size_t size : sizes) {

        vector<string> data;
        for (size_t i = 0; i < size; ++i) {
            data.push_back(generateRandomString(10 + (i % 11)));
        }

        AVLTree avlTree;
        auto start = high_resolution_clock::now();
        for (const auto& elem : data) {
            avlTree.insert(elem);
        }
        auto end = high_resolution_clock::now();
        auto avlTime = duration_cast<microseconds>(end - start);

        set<string> stdSet;
        start = high_resolution_clock::now();
        for (const auto& elem : data) {
            stdSet.insert(elem);
        }
        end = high_resolution_clock::now();
        auto setTime = duration_cast<microseconds>(end - start);

        double ratio = (double)avlTime.count() / setTime.count();

        cout << size << "," << avlTime.count() << "," << setTime.count() << "," << ratio << endl;
    }
}

void testFileInput(const string& filename) {
    cout << "\n=== Testing with input file: " << filename << " ===" << endl;

    ifstream file(filename);
    if (!file) {
        cerr << "Cannot open input file: " << filename << endl;
        cerr << "Creating sample input file..." << endl;

        ofstream outFile(filename);
        if (outFile) {
            outFile << "apple\nbanana\ncherry\ndate\nelderberry\nfig\ngrape\n";
            outFile.close();
            file.open(filename);
        }
        else {
            cerr << "Failed to create input file" << endl;
            return;
        }
    }

    AVLTree tree;
    string line;
    size_t lineCount = 0;

    auto start = high_resolution_clock::now();
    while (getline(file, line)) {
        if (!line.empty()) {
            tree.insert(line);
            lineCount++;
        }
    }
    auto end = high_resolution_clock::now();
    file.close();

    auto duration = duration_cast<microseconds>(end - start);
    cout << "Inserted " << lineCount << " lines from file in "
        << duration.count() << " microseconds" << endl;
    cout << "Tree size: " << tree.size() << endl;
    cout << "Tree height: " << tree.getHeight() << endl;

    if (tree.isBalanced()) {
        cout << "Tree is balanced [OK]" << endl;
    }
    else {
        cerr << "Tree is NOT balanced after file input!" << endl;
    }

    if (tree.isBST()) {
        cout << "Tree is valid BST [OK]" << endl;
    }
    else {
        cerr << "Tree is NOT a valid BST!" << endl;
    }

    file.open(filename);
    size_t foundCount = 0;
    while (getline(file, line)) {
        if (!line.empty() && tree.contains(line)) {
            foundCount++;
        }
    }
    file.close();

    cout << "Found " << foundCount << " out of " << lineCount
        << " lines in tree" << endl;

    if (foundCount == lineCount) {
        cout << "All elements from file are in the tree [OK]" << endl;
    }
    else {
        cerr << "ERROR: Some elements from file are missing from tree!" << endl;
    }
}

int main(int argc, char* argv[]) {
    cout << "=== Lab 5: AVL Tree Container Implementation ===" << endl;

    int choice = 0;
    if (argc > 1) {
        choice = atoi(argv[1]);
    }

    switch (choice) {
    case 1:
        testBasicFunctionality();
        break;

    case 2:
        stressTest(10000);
        break;

    case 3:
        if (argc > 2) {
            size_t count = atoi(argv[2]);
            generateInputFile("test_data.txt", count);
        }
        else {
            generateInputFile("test_data.txt", 1000);
        }
        break;

    case 4:
        compareWithStdSet("test_data.txt");
        break;

    case 5:
        performanceComparison();
        break;

    case 6:
        testFileInput("input.txt");
        break;

    default:
        testBasicFunctionality();
        stressTest(1000);
        generateInputFile("test_data.txt", 1000);
        compareWithStdSet("test_data.txt");
        testFileInput("input.txt");
        cout << "\nFor specific tests, run with argument:" << endl;
        cout << "  1 - Basic functionality test" << endl;
        cout << "  2 - Stress test" << endl;
        cout << "  3 <count> - Generate test file" << endl;
        cout << "  4 - Compare with std::set" << endl;
        cout << "  5 - Performance comparison (CSV output)" << endl;
        cout << "  6 - Test with input.txt file" << endl;
        break;
    }

    return 0;
}