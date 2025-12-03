#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <iomanip>

#include "strset.h"

using namespace std;

struct Res {
    string label;
    long long time;
};

vector<Res> res;

vector<string> random_data(int count)
{
    vector<string> data;
    data.reserve(count);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, count * 10);

    for (int i = 0; i < count; ++i)
        data.push_back("key_" + to_string(dist(gen)));

    return data;
}

long long measure_stringset_insert(const vector<string>& data)
{
    auto start = chrono::high_resolution_clock::now();

    StringSet* myset = string_set_create();
    for (const auto& key : data)
        string_set_insert(myset, key);
    string_set_delete(myset);

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

long long measure_stdset_insert(const vector<string>& data)
{
    auto start = chrono::high_resolution_clock::now();

    std::set<string> stdset;
    for (const auto& key : data)
        stdset.insert(key);

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

void run_test(const string& suffix, const vector<string>& data)
{
    long long t_my = measure_stringset_insert(data);
    long long t_std = measure_stdset_insert(data);

    res.push_back({ "StringSet " + suffix, t_my });
    res.push_back({ "std::set " + suffix, t_std });
}

void cmp_with_random(int size)
{
    auto test = random_data(size);

    auto start = chrono::high_resolution_clock::now();
    StringSet* myset = string_set_create();

    for (const auto& key : test)
        string_set_insert(myset, key);

    auto end = chrono::high_resolution_clock::now();
    long long time_my = chrono::duration_cast<chrono::microseconds>(end - start).count();

    string_set_delete(myset);

    start = chrono::high_resolution_clock::now();
    std::set<string> stdset;

    for (const auto& key : test)
        stdset.insert(key);

    end = chrono::high_resolution_clock::now();
    long long time_std = chrono::duration_cast<chrono::microseconds>(end - start).count();

    res.push_back({ "StringSet (" + to_string(size) + ")", time_my });
    res.push_back({ "std::set (" + to_string(size) + ")", time_std });
}

void cmp_random_all()
{
    vector<int> sizes = {
        1000,
        5000,
        10000,
        50000,
        100000,
        200000,
        500000,
        1000000
    };

    for (int s : sizes)
        cmp_with_random(s);
}

void print_time()
{
    cout << "\nResults (microseconds):\n\n";

    for (auto& r : res)
    {
        cout << left << setw(25) << r.label << " | "
            << right << setw(12) << r.time << " us\n";
    }
}


int main(int argc, char* argv[])
{
    string filename = "input.txt";
    if (argc > 1)
        filename = argv[1];

    ifstream fin(filename);
    vector<string> words;
    string w;
    while (fin >> w)
        words.push_back(w);
    fin.close();

    cout << "File test: \"" << filename << "\", words = " << words.size() << "\n";

    run_test("(file)", words);

    cmp_random_all();

    print_time();

    return 0;
}