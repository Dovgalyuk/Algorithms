#include<iostream>
#include<string>
#include<chrono>
#include<random>
#include<unordered_map>
#include "associative_array.h"

const char chars[] = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };

std::string rand_str()
{
	int size = rand() % 10 +1;
	std::string str;
	for (int i = 0; i < size; i++)
	{
		str.push_back(chars[rand() % 62]);
	}
	return str;
}

void info(associative_array* associative_arr, std::unordered_map<std::string, std::string> map, int after)
{
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	insert_pair(rand_str(), rand_str(), associative_arr);
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
	std::chrono::duration<double> sec = end - start;
	std::cout << "insert after " << after << " elements \t| My own Hash table:" << sec.count() << " sec. \t| unordered_map: ";
	start = std::chrono::system_clock::now();
	map[rand_str()] = rand_str();
	end = std::chrono::system_clock::now();
	sec = end - start;
	std::cout << sec.count() << " sec.\n";
}

int main()
{
	associative_array* associative_arr = associative_array_create();
	std::unordered_map<std::string, std::string> map;

	std::string str;
	for (int i = 0; i < 100; i++)
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 100);

	for (int i = 0; i < 899; i++)
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 1000);

	for (int i = 0; i < 3999; i++)
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 5000);

	for (int i = 0; i < 4999; i++)
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 10000);

	for (int i = 0; i < 39999; i++)
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 50000);

	for (int i = 0; i < 49999; i++)
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 100000);

	for (int i = 0; i < 99999; i++)
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 200000);

	for (int i = 0; i < 299999; i++)
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 500000);

	for (int i = 0; i < 499999; i++)
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 1000000);

	for (int i = 0; i < 199999; i++)
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 1200000);

	associative_array_delete(associative_arr);
}