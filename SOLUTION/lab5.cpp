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
	std::cout << "insert after "<< after <<" elements| My own Hash table:" << sec.count() << " sec. | unordered_map: ";
	start = std::chrono::system_clock::now();
	map[rand_str()] = rand_str();
	sec = end - start;
	std::cout << sec.count() << " sec.\n";
}

int main()
{
	associative_array* associative_arr = associative_array_create();
	std::unordered_map<std::string, std::string> map;

	std::string str;
	for (int i = 0; i < 100; i++) // 100
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 100);
	for (int i = 0; i < 1000; i++) //1101
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 1000);
	for (int i = 0; i < 5000; i++) //5102
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 5000);
	for (int i = 0; i < 10000; i++) //15103
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 10000);
	for (int i = 0; i < 50000; i++) //65104
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 50000);
	for (int i = 0; i < 100000; i++) //165105
	{
		str = rand_str();
		map[str] = str;
		insert_pair(str, str, associative_arr);
	}
	info(associative_arr, map, 100000);
	associative_array_delete(associative_arr);
}