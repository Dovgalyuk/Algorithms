#include <iostream>
#include "map.hpp"
#include <string>
#include <chrono>
#include <map>

using namespace std;

int main()
{
	auto start_time = std::chrono::steady_clock::now();
	Map<int, int> test;
	for (int i = 0; i < 10000; i++)
		test.add(i, i);
	for (int i = 0; i < 10000; i++)
	{
		MapPair<int, int>* temp = test.find(i);
		if (!temp || temp->second() != i)
			cout << i << endl;
	}
	/*for (int i = 0; i < 10000; i++)
		test.add(i, i);
	for (int i = 0; i < 10000; i += 2)
		test.RemovePair(i);
	for (int i = 1; i < 10000; i += 2)
		test.find(i);
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns_Map = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	start_time = std::chrono::steady_clock::now();
	map<int, int> test1;
	for (int i = 0; i < 10000; i++)
		test1[i] = i;
	for (int i = 0; i < 10000; i += 2)
		test1.erase(i);
	for (int i = 1; i < 10000; i += 2)
		test1.find(i);
	end_time = std::chrono::steady_clock::now();
	auto elapsed_ns_map = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	cout << elapsed_ns_Map.count() / elapsed_ns_map.count() << endl;*/
}