#include "filter_bloom.h"
#include <vector>
#include <functional>
#include <string>

using namespace std;

struct FilterBloom {

    vector<bool> bits;
    size_t size;
    vector<function<size_t(string)>> hash_functions;

};

FilterBloom* f_create(size_t size, size_t num_hashes)
{
    FilterBloom* filter = new FilterBloom;

    filter->size = size;
    filter->bits.resize(size, false);

    for (size_t i = 0; i < num_hashes; i++) {

        filter->hash_functions.push_back([i, size](string value) {
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

        size_t index = a(value);

        if (index < filter->bits.size()) {
            filter->bits[index] = true;
        }
    }
}

bool f_contains(FilterBloom* filter,string& value) {

    for (auto& a : filter->hash_functions) {
        size_t index = a(value);

        if (index >= filter->bits.size() || !filter->bits[index]) {
            return false;
        }
    }

    return true;
}

void f_remove(FilterBloom* filter,string& value) {

    for (auto& a : filter->hash_functions) {

        size_t index = a(value);

        if (index < filter->bits.size()) {
            filter->bits[index] = false;
        }
    }
}