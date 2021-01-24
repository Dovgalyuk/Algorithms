#include "map.h"

struct Map
{
	binaryTree* root;
};

Map* createMap(const Key& key, const Data& value)
{
	Map* arr = new Map;
	arr->root = createBinTree(key, value);
	return arr;
}
Map* deleteMap(Map* arr)
{
	arr->root = deleteBinTree(arr->root);
	delete arr;
	return nullptr;
}
void insertMapElem(Map* arr, const Key& key, const Data& value)
{
	arr->root = insertElem(arr->root, key, value);
}
void deleteMapElem(Map* arr, const Key& key)
{
	arr->root = deleteElem(arr->root, key);
}
Data findMapElem(Map* arr, const Key& key)
{
	return getTreeData(findElem(arr->root, key));
}