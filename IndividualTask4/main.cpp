#include <iostream>
#include <unordered_map>
#include "map.h"
#include <ctime>

#define map_size 500
#define str_size 10

string gen_rand_str()
{
	string rand_str;
	rand_str.resize(str_size);

	static const char char_set[] =
		"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < str_size; i++)
		rand_str += char_set[rand() % (sizeof(char_set) - 1)];

	return rand_str;
}

int main()
{
	srand(time(NULL));

	clock_t timeStart;
	clock_t timeEnd;

	string values[map_size];
	string keys[map_size];

	for (int i = 0; i < map_size; i++)
	{
		keys[i] = gen_rand_str();
		values[i] = gen_rand_str();
	}

	// test map.h

	Map* map = map_create();

	timeStart = clock();

	for (unsigned int i = 0; i < map_size; i++)
		set_pair(map, keys[i], values[i]);

	timeEnd = clock();

	map_delete(map);

	cout << "map.h time: " << (double)(timeEnd - timeStart) / CLOCKS_PER_SEC << endl;

	// test STL unordered_map 

	unordered_map<string, string> map_stl;

	timeStart = clock();

	for (int i = 0; i < map_size; i++)
		map_stl.insert(pair<string, string>(keys[i], values[i]));

	timeEnd = clock();

	std::cout << "STL unordered_map time: " << (double)(timeEnd - timeStart) / CLOCKS_PER_SEC << std::endl;

	return 0;
}