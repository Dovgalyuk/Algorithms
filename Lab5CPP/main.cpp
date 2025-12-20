#include "RBTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

vector<pair<string, string>> generate_data(int count) {
    vector<pair<string, string>> data;
    random_device random_device;
    mt19937 random_generator(random_device());

    for (int i = 0; i < count; i++) {
        string key = "user" + to_string(random_generator() % 1000000);
        string value = "email" + to_string(i) + "@test.com";
        data.push_back(make_pair(key, value));
    }
    return data;
}

void test() {
    RBTree tree;
    string value;

    tree.insert("name", "alice");
    tree.insert("age", "25");
    tree.insert("city", "london");

    if (tree.find("name", value) && value == "alice") cout << "test_get ok" << endl;

    tree.remove("age");
    if (!tree.find("age", value)) cout << "test_remove ok" << endl;

    if (tree.size() == 2) cout << "test_size ok" << endl;
}

void speed() {
    int sizes[] = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    int sizes_count = 7;

    cout << "\nspeed test:" << endl;
    cout << "size time" << endl;

    for (int i = 0; i < sizes_count; i++) {
        int size = sizes[i];
        vector<pair<string, string>> data = generate_data(size);

        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        RBTree tree;
        for (size_t j = 0; j < data.size(); j++) {
            tree.insert(data[j].first, data[j].second);
        }
        chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
        long long elapsed_time = chrono::duration_cast<chrono::microseconds>(end - start).count();

        cout << size << " " << elapsed_time << endl;
    }
}

void mapvsrbtree() {
    int sizes[] = { 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };
    int sizes_count = 7;

    ofstream csv_file("сравнение.csv");

    cout << "\ncomparison with map:" << endl;
    cout << "size rbtree map" << endl;

    csv_file << "size,rbtree,std::map" << endl;

    for (int i = 0; i < sizes_count; i++) {
        int size = sizes[i];
        vector<pair<string, string>> data = generate_data(size);

        chrono::high_resolution_clock::time_point start_rb = chrono::high_resolution_clock::now();
        RBTree tree;
        for (size_t j = 0; j < data.size(); j++) {
            tree.insert(data[j].first, data[j].second);
        }
        chrono::high_resolution_clock::time_point end_rb = chrono::high_resolution_clock::now();
        long long time_rb = chrono::duration_cast<chrono::microseconds>(end_rb - start_rb).count();

        chrono::high_resolution_clock::time_point start_map = chrono::high_resolution_clock::now();
        map<string, string> std_map;
        for (size_t j = 0; j < data.size(); j++) {
            std_map[data[j].first] = data[j].second;
        }
        chrono::high_resolution_clock::time_point end_map = chrono::high_resolution_clock::now();
        long long time_map = chrono::duration_cast<chrono::microseconds>(end_map - start_map).count();

        cout << size << " " << time_rb << " " << time_map << endl;
        csv_file << size << "," << time_rb << "," << time_map << endl;
    }
    csv_file.close();
}

void stress() {
    int sizes[] = { 1000, 2000, 4000, 8000, 16000, 32000 };
    int sizes_count = 6;

    cout << "\nstress test:" << endl;
    cout << "size time" << endl;

    for (int i = 0; i < sizes_count; i++) {
        int size = sizes[i];
        vector<pair<string, string>> data = generate_data(size);

        chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
        RBTree tree;
        for (size_t j = 0; j < data.size(); j++) {
            tree.insert(data[j].first, data[j].second);
        }
        chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
        long long elapsed_time = chrono::duration_cast<chrono::microseconds>(end - start).count();

        cout << size << " " << elapsed_time << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Error: File not specified" << endl;
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        cout << "Error: Cannot open file " << argv[1] << endl;
        return 1;
    }

    test();
    speed();
    mapvsrbtree();
    stress();

    RBTree tree;
    string line;
    int count = 0;

    while (getline(input_file, line)) {
        istringstream line_stream(line);
        string key, value;
        if (line_stream >> key >> value) {
            tree.insert(key, value);
            count++;
        }
    }

    cout << "loaded: " << count << endl;
    cout << "tree_size: " << tree.size() << endl;

    return 0;
}