#pragma once

//#include "binaryTree.h"
#include "AVLtree.h"

struct Map;

Map* createMap(const Key& key, const Data& value);
Map* deleteMap(Map* arr);
void insertMapElem(Map* arr, const Key& key, const Data& value);
void deleteMapElem(Map* arr, const Key& key);
Data findMapElem(Map* arr, const Key& key);