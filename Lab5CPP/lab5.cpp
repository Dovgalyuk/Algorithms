#include "filter_bloom.h"
#include <vector>
#include <chrono>
#include <unordered_set>
#include <vector>
#include<fstream>
#include<string>

using namespace std;
using namespace std::chrono;

vector<string> generacia_test(size_t count) {

	vector<string> test_values;

	for (size_t i = 0; i < count; i++) {
		test_values.push_back("test_value_" + to_string(i));
	}

	return test_values;
}


long long test_bloom(int data_size) {

	FilterBloom* filter = f_create(data_size * 10, 7);

	auto test_data = generacia_test(data_size);

	auto start = high_resolution_clock::now();

	for (auto& value : test_data) {
		f_insert(filter, value);
	}

	auto end = high_resolution_clock::now();

	long long time = duration_cast<milliseconds>(end - start).count();

	f_delete(filter);

	return time;
}

long long test_unordered_set(int data_size) {

	unordered_set<string> uset;
	auto test_data = generacia_test(data_size);

	auto start = high_resolution_clock::now();

	for (auto& value : test_data) {
		uset.insert(value);
	}

	auto end = high_resolution_clock::now();

	long long time = duration_cast<milliseconds>(end - start).count();

	return time;
}

void complexity_test() {

	vector<int> sizes = { 1000, 2000, 4000 , 8000 , 16000 };

	for (int a : sizes) {
		
		long long bloom_time = test_bloom(a);
		long long uset_time = test_unordered_set(a);

		double bloom_per_op = (double)bloom_time / a;
		double set_per_op = (double)uset_time / a;

		cout << "Size " << a << ": Bloom time per op: " << bloom_per_op << " ms, Unordered_set time per op: " << set_per_op << " ms" << endl;
	}
}

void performance_graph_data() {

	vector<int> sizes = { 1000, 5000, 10000, 50000, 100000 };

	for (int a : sizes) {

		long long bloom_time = test_bloom(a);
		long long uset_time = test_unordered_set(a);

		cout << a << " , " << bloom_time << " , " << uset_time << endl;
	}
}

int main(int argc, char** argv) {
	(void)argc;

	ifstream input(argv[1]);

	if (!input.is_open()) {
		return 1;
	}

	int data_size;
	input >> data_size;


	long long bloom_time = test_bloom(data_size);
	long long uset_time = test_unordered_set(data_size);

	cout << "Data size: " << data_size << endl;
	cout << "Bloom filter insert time: " << (bloom_time ? "PASS" : "FAIL") << endl;
	cout << "Unordered_set insert time: " << (uset_time ? "PASS" : "FAIL") << endl;

	
	cout << "\nComplexity analysis" << endl;
	complexity_test();

	cout << "\nPerformance data for graphing:" << endl;
	performance_graph_data();

	input.close();
}


