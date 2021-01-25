#include "set.h"

struct Set
{
	AvlNode* root;
};

Set* set_create()
{
	Set* set = new Set;
	set->root = nullptr;
	return set;
}

void set_insert(Set* set, const Data& data)
{
	avl_insert(data, set->root);
}

Data& set_find(Set* set, const Data& key)
{
	AvlNode* node = avl_find(key, set->root);
	if (node == nullptr)
	{
		// std::cout << "No provided key in set_find()!";
		std::string null;
		return null;
	}
	else
	{
		return node_data(node);
	}
}

bool set_remove(Set* set, const Data& key)
{
	if (!avl_remove(key, set->root))
	{
		// std::cout << "No provided key in set_remove()!";
		return false;
	}
	return true;
}

void set_output(Set* set)
{
	avl_inorder_print(set->root);
}

void set_delete(Set* set)
{
	avl_delete(set->root);
	delete set;
}
