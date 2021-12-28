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
	std::chrono::system_clock::time_point start1;
	std::chrono::system_clock::time_point end1;
	std::string* str_arr = new std::string[count];

	for (int i = 0; i < count; i++)
		str_arr[i] = rand_str();

	start = std::chrono::system_clock::now();
	for (int i = 0; i < count; i++)
	{
		insert_pair(str_arr[i], str_arr[i], associative_arr);
	}
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> sec = end - start;

	start1 = std::chrono::system_clock::now();
	for (int i = 0; i < count; i++)
	{
		map[str_arr[i]] = str_arr[i];
	}
	end1 = std::chrono::system_clock::now();
	std::chrono::duration<double> sec1 = end1 - start1;

	std::cout << "insert " << count << " elements in | My own Hash table: " << sec.count() << "  |  in unordered map: " << sec1.count() << "\n";
	delete[] str_arr;
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