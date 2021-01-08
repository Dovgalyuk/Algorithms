#include "map.h"

struct Map
{
	Node* root;
};

Map* map_create()
{
	Map* new_map= new Map;
	new_map->root = nullptr;
	return new_map;
}

bool map_add(Map* map, const Key& key, const Data& value)
{
	if (map->root == nullptr)
	{
		map->root = node_create();
		node_set(map->root, key, value);
		return true;
	}

	Node* new_node = node_create();
	node_set(new_node, key, value);
	if (node_add(map->root, new_node))
	{
		splay(new_node);
		map->root = new_node;
		return true;
	}
	return false;
}

Data map_get_value(Map* map,const Key& key)
{
	if (map->root == nullptr)
		return Data();

	Node* sought_node = node_find(map->root, key);
	if (sought_node != nullptr)
	{
		splay(sought_node);
		map->root = sought_node;
		return node_get_value(sought_node);
	}
	return Data();
}

bool map_set_value(Map* map,const Key& key, const Data& new_value)
{
	if (map->root == nullptr)
		return false;

	Node* sought_node = node_find(map->root, key);
	if (sought_node != nullptr)
	{
		splay(sought_node);
		map->root = sought_node;
		node_set(sought_node, key, new_value);
		return true;
	}
	return false;
}

bool map_remove(Map* map,const Key& key)
{
	if (map->root == nullptr)
		return false;

	Node* sought_node = node_find(map->root, key);
	if (sought_node == nullptr)
		return false;

	splay(sought_node);
	map->root = sought_node;
	map->root = root_remove(map->root);
	return true;
}

void map_delete(Map* map)
{
	if(map->root != nullptr)
		tree_delete( map -> root);
	delete map;
}

int map_tree_height(Map* map)
{
	if (map->root != nullptr)
		return tree_height(map->root, 1);
	return 0;
}

void map_print(Map* map){ print_tree(map->root); }//DEBUG