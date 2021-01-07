#include <stdlib.h>
#include "set.h"

struct Set 
{
	Node* root;
};

Set* set_create(const Key key)
{
	Set* set = new Set;
	set->root = splay_create(key);
	return set;
}

void set_insert(Set* set, const Key key)
{
	insert(set->root, key);
}

bool set_find(Set* set, const Key key)
{
	if (find(set->root, key))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void set_erase(Set* set, const Key key)
{
	erase(set->root, key);
}

Set* set_delete(Set* set)
{
	splay_delete(set->root);
	delete set;
	return NULL;
}