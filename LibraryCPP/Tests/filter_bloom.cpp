#include <filter_bloom.h>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

using namespace std;
using namespace std::chrono;

const int NUM = 1000000;

bool test(FilterBloom* filter , const string& name, ofstream& file) {
	if (!filter)
	{
		file << name << " filter creation error\n";
		return 1;
	}

	string value1 = "hello";
	string value2 = "world";
	string value3 = "bloom";

	f_insert(filter, value1);
	f_insert(filter, value2);

	if (!f_contains(filter, value1)) {
		file << "f_insert or f_contains error for value1\n";
		return 1;
	}

	if (!f_contains(filter, value2)) {
		file << "f_insert or f_contains error for value2\n";
		return 1;
	}

	if (f_contains(filter, value3)) {
		file << "f_contains false positive for value3\n";
		return 1;
	}


	f_remove(filter, value1);

	if (f_contains(filter, value1)) {
		file << "f_remove or f_contains error for value1\n";
		return 1;
	}

	if (!f_contains(filter, value2)) {
		file << "f_contains error for value2 after removing value1\n";
		return 1;
	}

	double fp_rate1 = estimate_false_positives(filter, 1000);
	file << "False positive: " << fp_rate1 * 100 << "%" << endl;

	FilterBloom* filter2;
	if (name == "Fast") {
		filter2 = f_create_fast(1000, 3);
	}
	else {
		filter2 = f_create_slow(1000, 3);
	}
	double fn_rate2 = estimate_false_negatives(filter2, 1000);
	file << "False negative: " << fn_rate2 * 100 << "%" << endl;
	f_delete(filter2);

	if (fn_rate2 > 0.0) {
		file << "Filter has false negatives!" << endl;
	}

	f_delete(filter);

	return false;
}

void performance_test(FilterBloom* filter , int num ,const string& name , ofstream& file) {

	file << "\n" << name << " performance:" << endl;

	auto start = high_resolution_clock::now();

	for (int i = 0; i < num; i++) {
		string val = "perf_test_" + to_string(i);
		f_insert(filter, val);
	}

	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
	
	file << name << " - Insert " << num << " elements: " << duration.count() << " ms" << endl;
	file << name << " - Time per operation: " << (double)duration.count() / num << " ms" << endl;

	f_delete(filter);
}



int main() {

	ofstream file("../../../LibraryCPP/Tests/result.txt");

	if (!file.is_open()) {
		return 1;
	}
	if (test(f_create_fast(1000, 3), "Fast" , file)) {
		return 1;
	}
	
	if (test(f_create_slow(1000, 3), "Slow" , file)) {
		return 1;
	}

	performance_test(f_create_fast(NUM, 7), NUM, "Fast filter" , file);
	performance_test(f_create_slow(NUM, 7), NUM, "Slow filter" , file);

	file.close();
	return 0;
}