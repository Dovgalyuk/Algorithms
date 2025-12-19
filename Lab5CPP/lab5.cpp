#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <algorithm>
#include <cassert>
#include <sstream>
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

    vector<size_t> testSizes = { 1000, 5000, 10000, 50000, 100000, 250000, 500000, 750000, min((size_t)1000000, lines.size()) };

    for (size_t testSize : testSizes) {
        if (testSize > lines.size()) continue;

        cout << "\n--- Test with " << testSize << " elements ---" << endl;

        vector<string> testData(lines.begin(), lines.begin() + testSize);

        AVLTree avlTree;
        auto start = high_resolution_clock::now();
        for (const auto& l : testData) {
            avlTree.insert(l);
        }
        auto end = high_resolution_clock::now();
        auto avlTime = duration_cast<milliseconds>(end - start);

        set<string> stdSet;
        start = high_resolution_clock::now();
        for (const auto& l : testData) {
            stdSet.insert(l);
        }
        end = high_resolution_clock::now();
        auto setTime = duration_cast<milliseconds>(end - start);

        cout << "AVLTree: " << avlTime.count() << " ms (height: " << avlTree.getHeight() << ")" << endl;
        cout << "std::set: " << setTime.count() << " ms" << endl;
        cout << "Ratio (AVL/std::set): " << (double)avlTime.count() / setTime.count() << endl;
    }
}

void performanceComparison() {
    cout << "\n=== Performance Comparison (CSV format) ===" << endl;
    cout << "Size,AVLTree(ms),std::set(ms),Ratio,AVLTree Height,Is Balanced,Is BST" << endl;

    vector<size_t> sizes = {
        100, 500, 1000, 5000, 10000,
        20000, 50000, 100000, 200000,
        300000, 400000, 500000, 600000,
        700000, 800000, 900000, 1000000
    };

    ofstream csvFile("performance_results.csv");
    csvFile << "Size,AVLTree(ms),std::set(ms),Ratio,AVLTree Height,Is Balanced,Is BST" << endl;

    for (size_t size : sizes) {
        cout << "Testing with " << size << " elements..." << endl;

        vector<string> data;
        data.reserve(size);
        for (size_t i = 0; i < size; ++i) {
            data.push_back(generateRandomString(10 + (i % 11)));
        }

        AVLTree avlTree;
        auto start = high_resolution_clock::now();
        for (const auto& elem : data) {
            avlTree.insert(elem);
        }
        auto end = high_resolution_clock::now();
        auto avlTime = duration_cast<milliseconds>(end - start);

        set<string> stdSet;
        start = high_resolution_clock::now();
        for (const auto& elem : data) {
            stdSet.insert(elem);
        }
        end = high_resolution_clock::now();
        auto setTime = duration_cast<milliseconds>(end - start);

        double ratio = setTime.count() > 0 ? (double)avlTime.count() / setTime.count() : 0;

        cout << size << ","
            << avlTime.count() << ","
            << setTime.count() << ","
            << ratio << ","
            << avlTree.getHeight() << ","
            << (avlTree.isBalanced() ? "Yes" : "No") << ","
            << (avlTree.isBST() ? "Yes" : "No") << endl;

        csvFile << size << ","
            << avlTime.count() << ","
            << setTime.count() << ","
            << ratio << ","
            << avlTree.getHeight() << ","
            << (avlTree.isBalanced() ? "Yes" : "No") << ","
            << (avlTree.isBST() ? "Yes" : "No") << endl;
    }

    csvFile.close();
    cout << "\nResults saved to performance_results.csv" << endl;

    cout << "\n=== Simple Console Chart ===" << endl;
    cout << "Size\tAVLTree(ms)\tstd::set(ms)" << endl;
    cout << "-----------------------------------" << endl;

    ifstream resultsFile("performance_results.csv");
    string header;
    getline(resultsFile, header);

    string row;
    while (getline(resultsFile, row)) {
        stringstream ss(row);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 3) {
            size_t size = stoi(tokens[0]);
            int avlTime = stoi(tokens[1]);
            int setTime = stoi(tokens[2]);

            cout << size << "\t" << avlTime << "\t\t" << setTime << endl;
        }
    }
    resultsFile.close();
}

void demoFileOperations() {
    cout << "\n=== Demonstration: File Operations ===" << endl;

    const string filename = "demo_input.txt";

    ofstream outFile(filename);
    if (outFile) {
        for (int i = 0; i < 50000; ++i) {
            outFile << generateRandomString(5 + (i % 15)) << endl;
        }
        outFile.close();
        cout << "Created demo file with 50000 strings: " << filename << endl;
    }

    AVLTree tree;
    ifstream file(filename);
    string line;
    size_t count = 0;

    auto start = high_resolution_clock::now();
    while (getline(file, line)) {
        if (!line.empty()) {
            tree.insert(line);
            count++;
        }
    }
    auto end = high_resolution_clock::now();
    file.close();

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Inserted " << count << " strings from file in "
        << duration.count() << " milliseconds" << endl;
    cout << "Tree size: " << tree.size() << endl;
    cout << "Tree height: " << tree.getHeight() << endl;
    cout << "Tree is balanced: " << (tree.isBalanced() ? "Yes" : "No") << endl;
    cout << "Tree is valid BST: " << (tree.isBST() ? "Yes" : "No") << endl;
}

void demoAVLTreeOperations() {
    cout << "\n=== Demonstration: AVLTree Operations ===" << endl;

    AVLTree tree;

    cout << "Inserting 5 strings..." << endl;
    vector<string> words = { "zebra", "apple", "mango", "banana", "cherry" };
    for (const auto& word : words) {
        tree.insert(word);
        cout << "  Inserted: " << word << endl;
    }

    cout << "\nTree size: " << tree.size() << endl;
    cout << "Tree height: " << tree.getHeight() << endl;

    cout << "\nRemoving 'mango'..." << endl;
    if (tree.remove("mango")) {
        cout << "  Successfully removed 'mango'" << endl;
    }

    cout << "\nCurrent tree size: " << tree.size() << endl;
    cout << "Tree is balanced: " << (tree.isBalanced() ? "Yes" : "No") << endl;

    cout << "\nAll elements:" << endl;
    auto elements = tree.getAllElements();
    for (const auto& elem : elements) {
        cout << "  " << elem << endl;
    }
}

int main(int argc, char* argv[]) {
    cout << "=== Lab 5: AVL Tree Container Demonstration ===" << endl;

    int choice = 0;
    if (argc > 1) {
        choice = atoi(argv[1]);
    }

    switch (choice) {
    case 1:
        demoAVLTreeOperations();
        break;

    case 2:
        if (argc > 2) {
            size_t count = atoi(argv[2]);
            stressTest(count);
        }
        else {
            stressTest(1000000);
        }
        break;

    case 3:
        if (argc > 2) {
            size_t count = atoi(argv[2]);
            generateInputFile("test_data.txt", count);
        }
        else {
            generateInputFile("test_data.txt", 1000000);
        }
        break;

    case 4:
        compareWithStdSet("test_data.txt");
        break;

    case 5:
        performanceComparison();
        break;

    case 6:
        demoFileOperations();
        break;

    default:
        cout << "\nAVL Tree Demonstration Menu:" << endl;
        cout << "  1 - AVLTree basic operations demo" << endl;
        cout << "  2 <count> - Stress test (default: 1,000,000)" << endl;
        cout << "  3 <count> - Generate test data file (default: 1,000,000)" << endl;
        cout << "  4 - Compare AVLTree with std::set" << endl;
        cout << "  5 - Performance comparison (CSV output + chart)" << endl;
        cout << "  6 - File operations demo" << endl;

        cout << "\nRunning performance comparison..." << endl;
        performanceComparison();
        break;
    }

    return 0;
}