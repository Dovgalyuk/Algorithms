#ifndef FILTER_BLOOM_H
#define FILTER_BLOOM_H

#include <iostream>
using namespace std;

struct FilterBloom;

FilterBloom* f_create(size_t size, size_t num_hashes);

void f_delete(FilterBloom* filter);

void f_insert(FilterBloom* filter, string& value);

bool f_contains(FilterBloom* filter, string& value);

void f_remove(FilterBloom* filter, string& value);

#endif