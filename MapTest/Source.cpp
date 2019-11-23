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
	for (int i = 0; i < 100; i++)
		test.add(i, i);
	for (int i = 0; i < 100; i += 2)
		test.RemovePair(i);
	for (int i = 0; i < test.data->size(); i++)
	{
		auto temp1 = test.data->get(i);
		if (temp1)
			cout << i << ' ' << temp1->first() << ' ' << temp1->Hash() % 100 << endl;
		else
			cout << i << ' ' << "none" << ' ' << "none" << endl;
	}
		
	/*for (int i = 0; i < 1000; i++)
		if (!test.find(i))
			cout << i << endl;*/
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns_Map = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	/*start_time = std::chrono::steady_clock::now();
	map<int, int> test1;
	for (int i = 0; i < 100000; i++)
		test1[i] = i;
	for (int i = 0; i < 100000; i += 2)
		test1.erase(i);
	for (int i = 1; i < 100000; i += 2)
		test1.find(i);
	end_time = std::chrono::steady_clock::now();
	auto elapsed_ns_map = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
	cout << endl << elapsed_ns_Map.count() << endl << elapsed_ns_map.count() << endl;*/
}