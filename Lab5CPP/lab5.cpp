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

void complexity_test(ofstream& file) {

	vector<int> sizes = { 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000 };
	vector<long long> bloom_times_fast, bloom_times_slow, uset_times;

	for (int a : sizes) {
		
		long long bloom_time_fast = test_bloom(f_create_fast(a * 10, 7), a);
		long long bloom_time_slow = test_bloom(f_create_slow(a * 10, 7), a);
		long long uset_time = test_unordered_set(a);

		bloom_times_fast.push_back(bloom_time_fast);	
		bloom_times_slow.push_back(bloom_time_slow);
		uset_times.push_back(uset_time);

	}

	long long max_time = 0;
	for (size_t i = 0; i < sizes.size(); i++) {
		max_time = max(max_time, max(bloom_times_fast[i], max(bloom_times_slow[i], uset_times[i])));
	}

	const int width = 100;

	for (size_t i = 0; i < sizes.size(); i++) {

		if (sizes[i] < 1000000) file << " ";
		if (sizes[i] < 100000) file << " ";
		if (sizes[i] < 10000) file << " ";
		if (sizes[i] < 1000) file << " ";
		file << sizes[i] << " | ";

		int f_pos = (int)((double)bloom_times_fast[i] / max_time * (width - 1));
		int s_pos = (int)((double)bloom_times_slow[i] / max_time * (width - 1));
		int u_pos = (int)((double)uset_times[i] / max_time * (width - 1));

		for (int j = 0; j <= width; j++) {

			if (j == f_pos && j == s_pos && j == u_pos) {
				file << "X"; // все три
			}
			else if (j == f_pos && j == s_pos) {
				file << "#"; //fast и slow
			}
			else if (j == f_pos && j == u_pos) {
				file << "$"; // fast и set
			}
			else if (j == s_pos && j == u_pos) {
				file << "&"; //slow и set
			}
			else if (j == f_pos) {
				file << "*"; // fast
			}
			else if (j == s_pos) {
				file << "+"; //slow
			}
			else if (j == u_pos) {
				file << "@"; //set
			}
			else {
				file << " ";
			}
		}

		file << "\n";
	}

	file << "\n* = Fast Bloom, + = Slow Bloom, @ = Unordered_set\n";
	file << "X = All three, # = Fast+Slow, $ = Fast+Set, & = Slow+Set\n";
}

void performance_graph_data(ofstream& file) {

	vector<int> sizes = { 1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000 };

	for (int a : sizes) {

		long long bloom_time_fast = test_bloom(f_create_fast(a * 10, 7), a);
		long long bloom_time_slow = test_bloom(f_create_slow(a * 10, 7), a);
		long long uset_time = test_unordered_set(a);


		long long fast_stars = bloom_time_fast / 100;// 100 ms
		long long slow_stars = bloom_time_slow / 100;
		long long set_stars = uset_time / 100;

		file << a << "," << bloom_time_fast << "," << bloom_time_slow << "," << uset_time << endl;

		file << "F:";
		for (long long i = 0; i < fast_stars && i < 20; i++) {
			file << "*";
		}

		file << " S:";
		for (long long i = 0; i < slow_stars && i < 20; i++) {
			file << "*";
		}

		file << " U:";
		for (long long i = 0; i < set_stars && i < 20; i++){
			file << "*";
		}
		file << endl;

	}


}

int main(int argc, char** argv) {
	(void)argc;

	ifstream input(argv[1]);
	ofstream file("../../Lab5CPP/result.txt");

	if (!input.is_open() || !file.is_open()) {
		return 1;
	}


	int data_size;
	input >> data_size;


	cout << "Data size: " << data_size;

	long long bloom_time_fast = test_bloom(f_create_fast(data_size * 10, 7), data_size);
	long long bloom_time_slow = test_bloom(f_create_slow(data_size * 10, 7), data_size);
	long long uset_time = test_unordered_set(data_size);

	file << "Data size: " << data_size << endl;
	file << "Fast Bloom filter time: " << bloom_time_fast << " ms" << endl;
	file << "Slow Bloom filter time: " << bloom_time_slow << " ms" << endl;
	file << "Unordered_set time: " << uset_time << " ms" << endl;

	
	file << "\nComplexity analysis" << endl;
	complexity_test(file);

	file << "\nPerformance data for graphing:" << endl;
	performance_graph_data(file);

	file.close();
	input.close();
}


