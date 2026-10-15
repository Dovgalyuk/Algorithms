#include <chrono>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "radix_map.h"
using namespace std;

typedef pair<string, string> Entry;
typedef vector<Entry> Data;

static string make_key(size_t number)
{
    ostringstream key;
    key << "word" << setw(10) << setfill('0') << number;
    return key.str();
}

static bool basic_test()
{
    RadixMap values;
    values.insert("", "empty");
    const string *empty_value = values.find("");
    if (empty_value == nullptr || *empty_value != "empty")
        return false;

    values.insert("apple", "red");
    values.insert("apple", "green");
    const string *apple = values.find("apple");
    if (apple == nullptr || *apple != "green" || values.find("apples") != nullptr)
        return false;
    if (values.erase("missing") || !values.erase("apple")
        || values.find("apple") != nullptr || !values.erase(""))
        return false;
    return values.entries().empty();
}

static bool prefix_test()
{
    RadixMap values;
    values.insert("car", "one");
    values.insert("cart", "two");
    values.insert("carbon", "three");
    values.insert("cat", "four");
    values.insert("ca", "prefix");

    RadixMap::Entries expected;
    expected.push_back(make_pair("ca", "prefix"));
    expected.push_back(make_pair("car", "one"));
    expected.push_back(make_pair("carbon", "three"));
    expected.push_back(make_pair("cart", "two"));
    expected.push_back(make_pair("cat", "four"));
    if (values.entries() != expected)
        return false;
    size_t position = 0;
    for (RadixMap::const_iterator it = values.begin(); it != values.end(); ++it, ++position)
        if (position >= expected.size() || *it != expected[position])
            return false;
    if (position != expected.size())
        return false;

    if (values.erase("cab") || !values.erase("ca")
        || values.find("car") == nullptr || values.find("cart") == nullptr)
        return false;
    if (!values.erase("car") || values.find("car") != nullptr
        || values.find("carbon") == nullptr || !values.erase("cart")
        || values.find("cat") == nullptr || !values.erase("carbon")
        || !values.erase("cat"))
        return false;
    return values.entries().empty();
}

static bool stress_test(size_t count)
{
    RadixMap values;
    for (size_t i = 0; i < count; ++i)
        values.insert(make_key(i), to_string(i));
    for (size_t i = 0; i < count; ++i)
    {
        const string *result = values.find(make_key(i));
        if (result == nullptr || *result != to_string(i))
            return false;
    }
    for (size_t i = 0; i < count; i += 2)
        if (!values.erase(make_key(i)))
            return false;
    for (size_t i = 0; i < count; ++i)
    {
        const string *result = values.find(make_key(i));
        if ((i % 2 == 0 && result != nullptr)
            || (i % 2 != 0 && (result == nullptr || *result != to_string(i))))
            return false;
    }
    for (size_t i = 1; i < count; i += 2)
        if (!values.erase(make_key(i)))
            return false;
    return values.entries().empty();
}

static bool generate(const string &path, size_t count)
{
    ofstream file(path.c_str());
    if (!file)
        return false;
    for (size_t i = 0; i < count; ++i)
        file << make_key(i) << " value" << i << '\n';
    return file.good();
}

static bool test_generator(const string &path, size_t count)
{
    if (!generate(path, count))
        return false;

    ifstream file(path.c_str());
    string key;
    string value;
    for (size_t i = 0; i < count; ++i)
    {
        if (!(file >> key >> value) || key != make_key(i)
            || value != "value" + to_string(i))
            return false;
    }
    if (file >> key >> value)
        return false;
    file.close();
    remove(path.c_str());
    return true;
}

template <typename Container>
static double measure(Container &values, const Data &data)
{
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    for (Data::const_iterator it = data.begin(); it != data.end(); ++it)
        values[it->first] = it->second;
    chrono::steady_clock::time_point finish = chrono::steady_clock::now();
    return chrono::duration<double, milli>(finish - start).count();
}

static double measure_radix(const Data &data)
{
    RadixMap values;
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    for (Data::const_iterator it = data.begin(); it != data.end(); ++it)
        values.insert(it->first, it->second);
    chrono::steady_clock::time_point finish = chrono::steady_clock::now();
    return chrono::duration<double, milli>(finish - start).count();
}

static bool benchmark(const string &input_path, const string &csv_path)
{
    const size_t sizes[] = {1000, 10000, 100000, 1000000};
    Data all_data;
    ifstream input(input_path.c_str());
    string key;
    string value;
    while (input >> key >> value)
        all_data.push_back(make_pair(key, value));
    if (!input.eof() || all_data.size() < sizes[3])
        return false;

    ofstream csv(csv_path.c_str());
    if (!csv)
        return false;
    csv << "count,radix_ms,map_ms,unordered_map_ms\n";
    for (size_t i = 0; i < 4; ++i)
    {
        Data data(all_data.begin(), all_data.begin() + sizes[i]);
        map<string, string> ordered;
        unordered_map<string, string> hashed;
        hashed.reserve(data.size());
        double radix_time = measure_radix(data);
        double map_time = measure(ordered, data);
        double hash_time = measure(hashed, data);
        csv << sizes[i] << ',' << radix_time << ',' << map_time << ',' << hash_time << '\n';
        cout << sizes[i] << ": " << radix_time << " ms, " << map_time
                  << " ms, " << hash_time << " ms\n";
    }
    return csv.good();
}

static bool benchmark_test(const string &input_path, const string &csv_path)
{
    if (!generate(input_path, 1000000) || !benchmark(input_path, csv_path))
        return false;

    ifstream csv(csv_path.c_str());
    string line;
    if (!getline(csv, line) || line != "count,radix_ms,map_ms,unordered_map_ms")
        return false;

    const size_t expected[] = {1000, 10000, 100000, 1000000};
    for (size_t i = 0; i < 4; ++i)
    {
        if (!getline(csv, line))
            return false;
        stringstream row(line);
        size_t count;
        char comma;
        double radix_time;
        double map_time;
        double hash_time;
        if (!(row >> count >> comma) || comma != ','
            || !(row >> radix_time >> comma) || comma != ','
            || !(row >> map_time >> comma) || comma != ','
            || !(row >> hash_time) || count != expected[i]
            || radix_time <= 0 || map_time <= 0 || hash_time <= 0)
            return false;
    }
    if (getline(csv, line))
        return false;
    csv.close();
    remove(input_path.c_str());
    remove(csv_path.c_str());
    return true;
}

int main(int argc, char **argv)
{
    if (argc == 2 && string(argv[1]) == "--test-basic")
        return basic_test() ? 0 : 1;
    if (argc == 2 && string(argv[1]) == "--test-prefixes")
        return prefix_test() ? 0 : 1;
    if (argc == 3 && string(argv[1]) == "--test-stress")
        return stress_test(static_cast<size_t>(stoull(argv[2]))) ? 0 : 1;
    if (argc == 4 && string(argv[1]) == "--test-generator")
        return test_generator(argv[2], static_cast<size_t>(stoull(argv[3]))) ? 0 : 1;
    if (argc == 4 && string(argv[1]) == "--test-benchmark")
        return benchmark_test(argv[2], argv[3]) ? 0 : 1;
    if (argc == 4 && string(argv[1]) == "--generate")
        return generate(argv[2], static_cast<size_t>(stoull(argv[3]))) ? 0 : 1;
    if (argc == 4 && string(argv[1]) == "--benchmark")
        return benchmark(argv[2], argv[3]) ? 0 : 1;
    cerr << "Usage: Lab5 --test-basic | --test-prefixes | --test-stress count | --test-generator file count | --test-benchmark input csv | --generate file count | --benchmark input csv\n";
    return 1;
}
