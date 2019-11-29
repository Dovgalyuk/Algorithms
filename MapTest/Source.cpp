#include <iostream>
#include "map.hpp"
#include <string>
#include <chrono>
#include <map>

using namespace std;

int main()
{
	auto start_time = std::chrono::steady_clock::now();
	const int len = 100000;
	Map<int, int, 179> test;
	for (int i = 0; i < len; i++)
		test.add(i, i);
	for (int i = 0; i < len; i += 2)
		test.RemovePair(i);
	for (int i = 1; i < len; i += 2)
		test.find(i);
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns_Map = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	start_time = std::chrono::steady_clock::now();
	map<int, int> test1;
	for (int i = 0; i < len; i++)
		test1[i] = i;
	for (int i = 0; i < len; i += 2)
		test1.erase(i);
	for (int i = 1; i < len; i += 2)
		test1.find(i);
	end_time = std::chrono::steady_clock::now();
	auto elapsed_ns_map = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	cout << elapsed_ns_Map.count() << endl << elapsed_ns_map.count() << endl;
}