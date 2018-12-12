#include "stdafx.h"
#include <iostream>
#include "tree.h"

using namespace std;

struct Leaf
{
	Data value;
	Leaf* left;
	Leaf* right;
	Leaf* parent;
	int height;
};

struct Tree
{
	Leaf* root;
};

//Создаёт дерево.
Tree* tree_create()
{
	Tree* NewTree;

	try
	{
		NewTree = new Tree;
		NewTree->root = new Leaf;
	}
	catch (bad_alloc xa)
	{
		cout << "Tree didn't create" << endl;
		return NULL;
	}

	NewTree->root->height = 0;
	NewTree->root->parent = NULL;
	NewTree->root->value = -8000000;
	NewTree->root->left = NULL;
	NewTree->root->right = NULL;

	return NewTree;
}

//Добавляет значение в дерево.
void insert(Leaf* leaf, Data value)
{
	if ((leaf->left == NULL) && (leaf->right == NULL))
	{
		Leaf* NewLeaf;

		try
		{
			NewLeaf = new Leaf;
		}
		catch (bad_alloc xa)
		{
			cout << "Leaf didn't create" << endl;
			return;
		}

		leaf->left = NewLeaf;
		leaf->left->value = value;
		leaf->left->height = leaf->height + 1;
		leaf->left->parent = leaf;
		NewLeaf->left = NULL;
		NewLeaf->right = NULL;
	}
	else if (leaf->left == NULL)
	{
		if (leaf->right->value < value)
		{
			insert(leaf->right, value);
		}

		Leaf* NewLeaf;

		try
		{
			NewLeaf = new Leaf;
		}
		catch (bad_alloc xa)
		{
			cout << "Leaf didn't create" << endl;
			return;
		}
		leaf->left = NewLeaf;
		leaf->left->value = value;
		leaf->left->height = leaf->height + 1;
		leaf->left->parent = leaf;
		NewLeaf->left = NULL;
		NewLeaf->right = NULL;
	}
	else if (leaf->right == NULL)
	{
		if (leaf->left->value < value)
		{
			insert(leaf->left, value);
		}
		
		Leaf* NewLeaf;

		try
		{
			NewLeaf = new Leaf;
		}
		catch (bad_alloc xa)
		{
			cout << "Leaf didn't create" << endl;
			return;
		}

		leaf->right = NewLeaf;
		leaf->right->value = value;
		leaf->right->height = leaf->height + 1;
		leaf->right->parent = leaf;
		NewLeaf->left = NULL;
		NewLeaf->right = NULL;
	}
	else
	{
		if (leaf->left->value < value)
		{
			insert(leaf->left, value);
		}
		if (leaf->right->value < value)
		{
			insert(leaf->right, value);
		}
	}
}

Leaf* get_root(const Tree* tree)
{
	return tree->root;
}

void get_result_length(Leaf* leaf)
{
	Leaf* tmp = leaf;

	while ((tmp->left != NULL) || (tmp->right != NULL))
	{
		if (tmp->left == NULL)
		{
			tmp = tmp->right;
		}
		else if (tmp->right == NULL)
		{
			tmp = tmp->left;
		}
		else
		{
			if (tmp->left->value < tmp->right->value)
			{
				tmp = tmp->left;
			}
			else if (tmp->left->value > tmp->right->value)
			{
				tmp = tmp->right;
			}
		}

		cout << tmp->value << " ";
	}

	cout << endl;
}

void get_result_hight(Leaf* leaf)
{
	if ((leaf->left == NULL) && (leaf->right == NULL))
	{
		cout << leaf->height << endl;
	}
	else if (leaf->left == NULL)
	{
		get_result_hight(leaf->right);
	}
	else if (leaf->right == NULL)
	{
		get_result_hight(leaf->left);
	}
	else
	{
		if (leaf->left->value < leaf->right->value)
		{
			get_result_hight(leaf->left);
		}
		else if (leaf->left->value > leaf->right->value)
		{
			get_result_hight(leaf->right);
		}
	}
}
