#include <map>
#include "map.h"
#include <ctime>

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

   Map* mapH = map_create();

   timeStart = clock();

   for (int i = 0; i < ArraySize; i++)
      map_insert(mapH, mapData[i], mapKey[i]); 

   timeEnd = clock();

   map_delete(mapH);

   std::cout << "MAP_H TIME: " << (double)(timeEnd - timeStart) / CLOCKS_PER_SEC << std::endl; 

   // Test STL map 

   std::map<std::string, std::string> mapStl;

   timeStart = clock();

   for (int i = 0; i < ArraySize; i++)
      mapStl.insert(std::pair<std::string, std::string>(mapKey[i], mapData[i]));

   timeEnd = clock();

   std::cout << "MAP_STL TIME: " << (double)(timeEnd - timeStart) / CLOCKS_PER_SEC << std::endl; 

   return 0;
}
