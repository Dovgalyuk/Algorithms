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


long long test_bloom(FilterBloom* filter , int data_size) {

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

	vector<int> sizes = { 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000 };

	for (int a : sizes) {
		
		long long bloom_time_fast = test_bloom(f_create_fast(a * 10, 7), a);
		long long bloom_time_slow = test_bloom(f_create_slow(a * 10, 7), a);
		long long uset_time = test_unordered_set(a);

		double bloom_per_op_fast = (double)bloom_time_fast / a;
		double bloom_per_op_slow = (double)bloom_time_slow / a;
		double set_per_op = (double)uset_time / a;

		cout << "Size : " << a << " Fast = " << bloom_per_op_fast << " ms, Slow = " << bloom_per_op_slow <<  " ms, Set = " << set_per_op << " ms" << endl;
	}
}

void performance_graph_data() {

	vector<int> sizes = { 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000 };

	for (int a : sizes) {

		long long bloom_time_fast = test_bloom(f_create_fast(a * 10, 7), a);
		long long bloom_time_slow = test_bloom(f_create_slow(a * 10, 7), a);
		long long uset_time = test_unordered_set(a);


		long long fast_stars = bloom_time_fast / 100;// 100 ms
		long long slow_stars = bloom_time_slow / 100;
		long long set_stars = uset_time / 100;

		cout << a << "," << bloom_time_fast << "," << bloom_time_slow << "," << uset_time << endl;

		cout << "F:";
		for (long long i = 0; i < fast_stars && i < 20; i++) {
			cout << "*";
		}

		cout << " S:";
		for (long long i = 0; i < slow_stars && i < 20; i++) {
			cout << "*";
		}

		cout << " U:";
		for (long long i = 0; i < set_stars && i < 20; i++){
			cout << "*";
		}
		cout << endl;

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


	long long bloom_time_fast = test_bloom(f_create_fast(data_size * 10, 7), data_size);
	long long bloom_time_slow = test_bloom(f_create_slow(data_size * 10, 7), data_size);
	long long uset_time = test_unordered_set(data_size);

	cout << "Data size: " << data_size << endl;
	cout << "Fast Bloom filter time: " << bloom_time_fast << " ms" << endl;
	cout << "Slow Bloom filter time: " << bloom_time_slow << " ms" << endl;
	cout << "Unordered_set time: " << uset_time << " ms" << endl;

	
	cout << "\nComplexity analysis" << endl;
	complexity_test();

	cout << "\nPerformance data for graphing:" << endl;
	performance_graph_data();

	input.close();
}


