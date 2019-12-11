#include <iostream>
#include "map.hpp"
#include <string>
#include <chrono>
#include <map>

using namespace std;

int main()
{
	const int len = 100000;
	int numbers[len];
	for (size_t i = 0; i < len; i++) {
		numbers[i] = i;
	}

	auto start_time = std::chrono::steady_clock::now();
	Map<int, int> test;
	for (int i = 0; i < len; i++)
		test.insert(numbers[i], numbers[i]);
	for (int i = 0; i < len; i += 2)
		test.erase(numbers[i]);
	for (int i = 1; i < len; i += 2)
		test.find(numbers[i]);
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns_Map = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	start_time = std::chrono::steady_clock::now();
	map<int, int> test1;
	for (int i = 0; i < len; i++)
		test1[numbers[i]] = numbers[i];
	for (int i = 0; i < len; i += 2)
		test1.erase(numbers[i]);
	for (int i = 1; i < len; i += 2)
		test1.find(numbers[i]);
	end_time = std::chrono::steady_clock::now();
	auto elapsed_ns_map = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	cout << elapsed_ns_Map.count() << endl << elapsed_ns_map.count() << endl;
}