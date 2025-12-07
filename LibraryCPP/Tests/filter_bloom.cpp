#include <filter_bloom.h>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

using namespace std;
using namespace std::chrono;

const int NUM = 1000000;

void draw_graph(ofstream& file, const string& label, double value) {

	file << label << ": [";

	int bars = (int)(value * 20);

	if (bars > 20){
		bars = 20;
	}

	for (int i = 0; i < 20; i++) {
		file << (i < bars ? "#" : " ");
	}

	file << "] " << value * 100 << "%";

}

void build_fp_graph(ofstream& file, const string& filter_name) {
	file << endl << filter_name << " - false_positives graph\n";

	for (int elements = 100; elements <= 900; elements += 200) {

		FilterBloom* filter;

		if (filter_name == "Fast") {
			filter = f_create_fast(1000, 3);
		}
		else {
			filter = f_create_slow(1000, 3);
		}

		for (int i = 0; i < elements; i++) {
			string val = "test_" + to_string(i);
			f_insert(filter, val);
		}

		double fp = estimate_false_positives(filter, 1000);
		draw_graph(file, to_string(elements) + " elem", fp);
		file << "\n";

		f_delete(filter);
	}
}

void build_fn_graph(ofstream& file, const string& filter_name) {
	file << endl << filter_name  << " - false_negatives graph\n";

	for (int removals = 100; removals <= 500; removals += 100) {

		FilterBloom* filter;

		if (filter_name == "Fast") {
			filter = f_create_fast(2000, 3);
		}
		else {
			filter = f_create_slow(2000, 3);
		}

		for (int i = 0; i < 1000; i++) {
			string val = "item_" + to_string(i);
			f_insert(filter, val);
		}

		for (int i = 0; i < removals; i++) {
			string val = "item_" + to_string(i);
			f_remove(filter, val);
		}

		double fn = estimate_false_negatives(filter, 1000);
		draw_graph(file, to_string(removals) + " rem", fn);
		file << "\n";

		f_delete(filter);

	}
}

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

	f_delete(filter);

	build_fp_graph(file, name);
	build_fn_graph(file, name);

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