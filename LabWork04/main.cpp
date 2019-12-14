#include <iostream>
#include "hashset.hpp"
#include <string>
#include <chrono>
#include <unordered_set>

using namespace std;

int main()
{
	auto start_time = std::chrono::steady_clock::now();
	const int len = 100000;
	hashSet <int> set;
	for (int i = 0; i < len; i++)
	{
		set.hash_add(i);
	}
	for (int i = 0; i < len; i += 2) {
		set.hash_remove(i);
	}
		
	for (int i = 1; i < len; i += 2)
		set.hash_search(i);

	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns_Map = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	start_time = std::chrono::steady_clock::now();
	unordered_set<int> test1;
	for (int i = 0; i < len; i++)
		test1.insert(i);
	for (int i = 0; i < len; i += 2)
		test1.erase(i);
	for (int i = 1; i < len; i += 2)
		test1.find(i);
	end_time = std::chrono::steady_clock::now();
	auto elapsed_ns_map = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	cout << elapsed_ns_Map.count() << endl << elapsed_ns_map.count() << endl;
}