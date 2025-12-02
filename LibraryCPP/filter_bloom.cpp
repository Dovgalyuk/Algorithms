#include "filter_bloom.h"
#include <vector>
#include <functional>
#include <string>

using namespace std;

struct FilterBloom {

    vector<bool> bits;
    size_t size;
    vector<function<size_t(string&)>> hash_functions;

};



FilterBloom* f_create_fast(size_t size, size_t num_hashes)
{
    FilterBloom* filter = new FilterBloom;

    filter->size = size;
    filter->bits.resize(size, false);

    for (size_t i = 0; i < num_hashes; i++) {

        filter->hash_functions.push_back([i, size](string& value) {
			hash<string> hasher;
			size_t hash1 = hasher(value);
		
            return (hash1 ^ (i * 0x9e3779b9)) % size;
            });

    }

    return filter;
}

FilterBloom* f_create_slow(size_t size, size_t num_hashes)
{
    FilterBloom* filter = new FilterBloom;

    filter->size = size;
    filter->bits.resize(size, false);

    for (size_t i = 0; i < num_hashes; i++) {

        filter->hash_functions.push_back([i, size](string& value) {
            return hash<string>{}(value + to_string(i)) % size;
            });

    }

    return filter;
}

void f_delete(FilterBloom* filter) {

    delete filter;

}

void f_insert(FilterBloom* filter,string& value) {

    for (auto& a : filter->hash_functions) {

        size_t index = a(value) % filter->size;

        if (index < filter->bits.size()) {
            filter->bits[index] = true;
        }
    }
}

bool f_contains(FilterBloom* filter,string& value) {

    for (auto& a : filter->hash_functions) {
        size_t index = a(value) % filter->size;

        if (!filter->bits[index]) {
            return false;
        }
    }

    return true;
}

void f_remove(FilterBloom* filter,string& value) {

    for (auto& a : filter->hash_functions) {

        size_t index = a(value) % filter->size;

        if (index < filter->bits.size()) {
            filter->bits[index] = false;
        }
    }
}

double estimate_false_positives(FilterBloom* filter, int num_tests) {
    int false_count = 0;

    for (int i = 0; i < num_tests; i++) {

        string test_str = "false_test_" + to_string(i);

        if (f_contains(filter, test_str)) {
            false_count++;
        }
    }

    return (double)false_count / num_tests;
}

double estimate_false_negatives(FilterBloom* filter, int num_tests) {

    int false_negatives = 0;
    vector<string> added_elements;

    for (int i = 0; i < num_tests; i++) {

        string elem = "test_" + to_string(i);
        f_insert(filter, elem);
        added_elements.push_back(elem);
    }

    for (auto& a : added_elements) {

        if (!f_contains(filter, a)) {
            false_negatives++;
        }
    }

    return (double)false_negatives / num_tests;
}