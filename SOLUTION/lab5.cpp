#include<iostream>
#include<string>
#include<chrono>
#include<random>
#include<unordered_map>
#include "associative_array.h"

const char chars[] = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };

std::string rand_str()
{
	int size = rand() % 10 + 1;
	std::string str;
	for (int i = 0; i < size; i++)
	{
		str.push_back(chars[rand() % 62]);
	}
	return str;
}

void Insert(associative_array* associative_arr, std::unordered_map<std::string, std::string> map, int count)
{
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	std::chrono::duration<double> sec{};
	std::chrono::system_clock::time_point start1;
	std::chrono::system_clock::time_point end1;
	std::chrono::duration<double> sec1{};
	std::string str;
	for (int i = 0; i < count; i++)
	{
		str = rand_str();
		start = std::chrono::system_clock::now();
		insert_pair(str, str, associative_arr);
		end = std::chrono::system_clock::now();
		sec += end - start;
		start1 = std::chrono::system_clock::now();
		map[str] = str;
		end1 = std::chrono::system_clock::now();
		sec1 += end1 - start1;

	}
	std::cout << "insert " << count << " elements in | My own Hash table: " << sec.count() << "  |  in unordered map: " << sec1.count() << "\n";
}


int main()
{
	associative_array* associative_arr = associative_array_create();
	std::unordered_map<std::string, std::string> map;

	Insert(associative_arr, map, 100);

	Insert(associative_arr, map, 500);

	Insert(associative_arr, map, 1000);

	Insert(associative_arr, map, 5000);

	Insert(associative_arr, map, 10000);

	Insert(associative_arr, map, 50000);

	Insert(associative_arr, map, 100000);

	Insert(associative_arr, map, 200000);

	Insert(associative_arr, map, 500000);

	Insert(associative_arr, map, 1000000);

	associative_array_delete(associative_arr);
}