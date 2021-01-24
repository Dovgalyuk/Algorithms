#include <map>
#include "map.h"
#include <ctime>
#include <iostream>

#define ArraySize 1000
#define StringLenght 10

std::string genRandomString()
{
	std::string resultString;
	resultString.resize(StringLenght);

	static const char charSet[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < StringLenght; i++)
		resultString += charSet[rand() % (sizeof(charSet) - 1)];

	return resultString;
}

int main()
{
	srand(time(NULL));

	clock_t timeStart;
	clock_t timeEnd;

	std::string mapData[ArraySize];
	std::string mapKey[ArraySize];

	for (int i = 0; i < ArraySize; i++)
	{
		mapData[i] = genRandomString();
		mapKey[i] = genRandomString();
	}

	// Test map.h

	Map* mapH = createMap("sdfsdfsdfdsfdsfs","fesfewfe");

	timeStart = clock();

	for (int i = 0; i < ArraySize; i++)
		insertMapElem(mapH, mapData[i], mapKey[i]);

	timeEnd = clock();


	std::cout << "MAP_H TIME insertMapElem: " << (double)(timeEnd - timeStart) / CLOCKS_PER_SEC << std::endl;

	//find Element
	
	timeStart = clock();

	for (int i = 0; i < ArraySize; i++)
		findMapElem(mapH, mapKey[i]);

	timeEnd = clock();

	std::cout << "MAP_H TIME findMapElem: " << (double)(timeEnd - timeStart) / CLOCKS_PER_SEC << std::endl;

	deleteMap(mapH);

	// Test STL map 

	std::map<std::string, std::string> mapStl;

	mapStl.insert(std::pair<std::string, std::string>("sdfsdfsdfdsfdsfs", "fesfewfe"));

	timeStart = clock();

	for (int i = 0; i < ArraySize; i++)
		mapStl.insert(std::pair<std::string, std::string>(mapKey[i], mapData[i]));

	timeEnd = clock();

	std::cout << "MAP_STL TIME insert: " << (double)(timeEnd - timeStart) / CLOCKS_PER_SEC << std::endl;

	timeStart = clock();

	for (int i = 0; i < ArraySize; i++)
		mapStl.find(mapKey[i]);

	timeEnd = clock();

	std::cout << "MAP_STL TIME find: " << (double)(timeEnd - timeStart) / CLOCKS_PER_SEC << std::endl;

	return 0;
}