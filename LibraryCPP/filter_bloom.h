#ifndef FILTER_BLOOM_H
#define FILTER_BLOOM_H

#include <iostream>
using namespace std;

struct FilterBloom;

FilterBloom* f_create_fast(size_t size, size_t num_hashes);
FilterBloom* f_create_slow(size_t size, size_t num_hashes);

void f_delete(FilterBloom* filter);

void f_insert(FilterBloom* filter, string& value);

bool f_contains(FilterBloom* filter, string& value);

void f_remove(FilterBloom* filter, string& value);

double estimate_false_positives(FilterBloom* filter, int num_tests = 1000);
double estimate_false_negatives(FilterBloom* filter, int num_tests = 1000);

#endif