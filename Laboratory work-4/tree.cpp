#include "stdafx.h"
#include <stdlib.h>
#include "tree.h"
#include <iostream>

using namespace std;

struct Leaf
{
	Data key;
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

Tree* tree_create()
{
	Tree* NewTree;

	try
	{
		NewTree = new Tree;
	}
	catch (bad_alloc xa)
	{
		cout << "Tree didn't create" << endl;
		return NULL;
	}

	NewTree->root = NULL;

	return NewTree;
}

int Max_Height(Leaf* leaf)
{
	if ((leaf->right == NULL) && (leaf->left == NULL))
	{
		return -1;
	}
	else if (leaf->right == NULL)
	{
		return leaf->left->height;
	}
	else if (leaf->left == NULL)
	{
		return leaf->right->height;
	}
	else if (leaf->right->height > leaf->left->height)
	{
		return leaf->right->height;
	}
	else if (leaf->right->height < leaf->left->height)
	{
		return leaf->left->height;
	}
	else
	{
		return leaf->left->height;
	}
}

int balance_leaf(Leaf* leaf)
{
	if ((leaf->right == NULL) && (leaf->left == NULL))
	{
		return 0;
	}
	else if (leaf->right == NULL)
	{
		return -1 - leaf->left->height;
	}
	else if (leaf->left == NULL)
	{
		return leaf->right->height + 1;
	}
	else
	{
		return leaf->right->height - leaf->left->height;
	}
}

void small_right_rotation(Tree* tree, Leaf* leaf)
{
	Leaf* tmp = leaf->right;
	tmp->parent = NULL;
	leaf->right = NULL;

	if (tmp->left != NULL)
	{
		tmp->left->parent = leaf;
	}

	leaf->right = tmp->left;
	tmp->left = leaf;
	tmp->parent = leaf->parent;

	if (tmp->parent != NULL)
	{
		if (tmp->parent->left == leaf)
		{
			tmp->parent->left = tmp;
		}
		else if (tmp->parent->right = leaf)
		{
			tmp->parent->right = tmp;
		}
	}

	leaf->parent = tmp;

	if (tree->root == leaf)
	{
		tree->root = tmp;
	}
}

void small_left_rotation(Tree* tree, Leaf* leaf)
{
	Leaf* tmp = leaf->left;
	tmp->parent = NULL;
	leaf->left = NULL;
	
	if (tmp->right != NULL)
	{
		tmp->right->parent = leaf;
	}

	leaf->left = tmp->right;
	tmp->right = leaf;
	tmp->parent = leaf->parent;

	if (tmp->parent != NULL)
	{
		if (tmp->parent->left == leaf)
		{
			tmp->parent->left = tmp;
		}
		else if (tmp->parent->right = leaf)
		{
			tmp->parent->right = tmp;
		}
	}

	leaf->parent = tmp;

	if (tree->root == leaf)
	{
		tree->root = tmp;
	}
}

void big_right_rotation(Tree* tree, Leaf* leaf)
{
	Leaf* Tmp = leaf->right;
	Leaf* tmp = leaf->right->left;

	leaf->right = NULL;
	Tmp->parent = NULL;
	tmp->parent = NULL;
	Tmp->left = NULL;

	Tmp->left = tmp->right;

	if (tmp->right != NULL)
	{
		tmp->right->parent = Tmp;
	}

	leaf->right = tmp->left;

	if (tmp->left != NULL)
	{
		tmp->left->parent = leaf;
	}

	tmp->right = Tmp;
	tmp->left = leaf;
	tmp->parent = leaf->parent;

	if (tmp->parent != NULL)
	{
		if (tmp->parent->right == leaf)
		{
			tmp->parent->right = tmp;
		}
		else if (tmp->parent->left == leaf)
		{
			tmp->parent->left = tmp;
		}
	}

	leaf->parent = tmp;
	Tmp->parent = tmp;

	if (tree->root == leaf)
	{
		tree->root = tmp;
	}
}

void big_left_rotation(Tree* tree, Leaf* leaf)
{
	Leaf* Tmp = leaf->left;
	Leaf* tmp = leaf->left->right;

	leaf->left = NULL;
	Tmp->parent = NULL;
	tmp->parent = NULL;
	Tmp->right = NULL;

	Tmp->right = tmp->left;

	if (tmp->left != NULL)
	{
		tmp->left->parent = Tmp;
	}
	
	leaf->left = tmp->right;

	if (tmp->right != NULL)
	{
		tmp->right->parent = leaf;
	}

	tmp->left = Tmp;
	tmp->right = leaf;
	tmp->parent = leaf->parent;

	if (tmp->parent != NULL)
	{
		if (tmp->parent->right == leaf)
		{
			tmp->parent->right = tmp;
		}
		else if (tmp->parent->left == leaf)
		{
			tmp->parent->left = tmp;
		}
	}

	leaf->parent = tmp;
	Tmp->parent = tmp;

	if (tree->root == leaf)
	{
		tree->root = tmp;
	}
}

void Balance(Tree* tree, Leaf* tmp)
{
	if ((balance_leaf(tmp) == 2) && ((balance_leaf(tmp->right) == 1) || (balance_leaf(tmp->right) == 0)))
	{
		small_right_rotation(tree, tmp);
		tmp->height = Max_Height(tmp) + 1;
		tmp = tmp->parent;
		tmp->height = Max_Height(tmp) + 1;
	}
	else if ((balance_leaf(tmp) == -2) && ((balance_leaf(tmp->left) == -1) || (balance_leaf(tmp->left) == 0)))
	{
		small_left_rotation(tree, tmp);
		tmp->height = Max_Height(tmp) + 1;
		tmp = tmp->parent;
		tmp->height = Max_Height(tmp) + 1;
	}
	if (tmp->right != NULL)
	{
		if ((balance_leaf(tmp) == 2) && ((balance_leaf(tmp->right->left) == -1) || (balance_leaf(tmp->right->left) == 1) || (balance_leaf(tmp->right->left) == 0)))
		{
			big_right_rotation(tree, tmp);
			tmp->height = Max_Height(tmp) + 1;
			tmp->parent->right->height = Max_Height(tmp->parent->right) + 1;
			tmp->parent->height = Max_Height(tmp->parent) + 1;
			tmp = tmp->parent;
		}
	}
	if (tmp->left != NULL)
	{
		if ((balance_leaf(tmp) == -2) && ((balance_leaf(tmp->left->right) == -1) || (balance_leaf(tmp->left->right) == 1) || (balance_leaf(tmp->left->right) == 0)))
		{
			big_left_rotation(tree, tmp);
			tmp->height = Max_Height(tmp) + 1;
			tmp->parent->left->height = Max_Height(tmp->parent->left) + 1;
			tmp->parent->height = Max_Height(tmp->parent) + 1;
			tmp = tmp->parent;
		}
	}
}

void insert_leaf(Tree* tree, Data key, Data value)
{
	Leaf* NewLeaf;

	try
	{
		NewLeaf = new Leaf;
	}
	catch (bad_alloc xa)
	{
		cout << "Cann't add leaf" << endl;
		return;
	}

	if (tree->root == NULL)
	{
		tree->root = NewLeaf;
		tree->root->key = key;
		tree->root->value = value;
		tree->root->height = 0;
		tree->root->left = NULL;
		tree->root->right = NULL;
		tree->root->parent = NULL;
	}
	else
	{
		Leaf* tmp = tree->root;

		while (true)
		{
			if (tmp->key <= key)
			{
				if (tmp->right == NULL)
				{
					tmp->right = NewLeaf;
					NewLeaf->parent = tmp;
					tmp = tmp->right;
					break;
				}

				tmp = tmp->right;
			}
			else if (tmp->key > key)
			{
				if (tmp->left == NULL)
				{
					tmp->left = NewLeaf;
					NewLeaf->parent = tmp;
					tmp = tmp->left;
					break;
				}

				tmp = tmp->left;
			}
		}

		tmp->key = key;
		tmp->value = value;
		tmp->height = 0;
		tmp->left = NULL;
		tmp->right = NULL;

		while (tmp != NULL)
		{
			tmp->height = Max_Height(tmp) + 1;
			Balance(tree, tmp);
			tmp = tmp->parent;
		}
	}
}

Leaf* get_root(Tree* tree)
{
	return tree->root;
}

Data get_root_key(Tree* tree)
{
	return tree->root->key;
}

Data get_value_of_leaf(const Tree* tree, Data key)
{
	Leaf* tmp = tree->root;

	while (tmp->key != key)
	{
		if (key > tmp->key)
		{
			if (tmp->right == NULL)
			{
				cout << "Element don't exist" << endl;
				return "";
			}

			tmp = tmp->right;
		}
		else if (key < tmp->key)
		{
			if (tmp->left == NULL)
			{
				cout << "Element don't exist" << endl;
				return "";
			}

			tmp = tmp->left;
		}
	}

	return tmp->value;
}

void delete_leaf(Tree* tree, Data key)
{
	Leaf* tmp = tree->root;

	while (tmp->key != key)
	{
		if (key >= tmp->key)
		{
			if (tmp->right == NULL)
			{
				cout << "Element don't exist" << endl;
				return;
			}

			tmp = tmp->right;
		}
		else if (key < tmp->key)
		{
			if (tmp->left == NULL)
			{
				cout << "Element don't exist" << endl;
				return;
			}

			tmp = tmp->left;
		}
	}

	//tmp - удаляемый элемент.

	if ((tmp->left == NULL) && (tmp->right == NULL))
	{
		Leaf* NewBalance = tmp->parent;
		
		if (NewBalance != NULL)
		{
			if (NewBalance->right == tmp)
			{
				NewBalance->right = NULL;
			}
			else if (NewBalance->left == tmp)
			{
				NewBalance->left = NULL;
			}
		}

		delete tmp;

		while (NewBalance != NULL)
		{
			NewBalance->height = Max_Height(NewBalance) + 1;
			Balance(tree, NewBalance);
			NewBalance = NewBalance->parent;
		}
	}
	else if (tmp->left == NULL)
	{
		//Связать правый элемент от удаляемого с родителем удаляемого элемента.
		Leaf* NewBalance = tmp->right;
		tmp->right->parent = tmp->parent;
		
		if (tmp->parent != NULL)
		{
			if (tmp->parent->left == tmp)
			{
				tmp->parent->left = tmp->right;
			}
			else if (tmp->parent->right == tmp)
			{
				tmp->parent->right = tmp->right;
			}
		}

		if (tree->root == tmp)
		{
			tree->root = NewBalance;
		}

		delete tmp;

		while (NewBalance != NULL)
		{
			NewBalance->height = Max_Height(NewBalance) + 1;
			Balance(tree, NewBalance);
			NewBalance = NewBalance->parent;
		}
	}
	else if (tmp->right == NULL)
	{
		//Связать левый элемент от удаляемого и родителя удаляемого элемента.

		Leaf* NewBalance = tmp->left;
		tmp->left->parent = tmp->parent;

		if (tmp->parent != NULL)
		{
			if (tmp->parent->right == tmp)
			{
				tmp->parent->right = tmp->left;
			}
			else if (tmp->parent->left == tmp)
			{
				tmp->parent->left = tmp->left;
			}
		}

		if (tree->root == tmp)
		{
			tree->root = NewBalance;
		}

		delete tmp;

		while (NewBalance != NULL)
		{
			NewBalance->height = Max_Height(NewBalance) + 1;
			Balance(tree, NewBalance);
			NewBalance = NewBalance->parent;
		}
	}
	else
	{
		Leaf* NewVertex = tmp->left;

		if (NewVertex->right == NULL)
		{
			NewVertex->parent = tmp->parent;

			if (tmp->parent != NULL)
			{
				if (tmp->parent->left == tmp)
				{
					tmp->parent->left = NewVertex;
				}
				else if (tmp->parent->right == tmp)
				{
					tmp->parent->right = NewVertex;
				}
			}

			tmp->right->parent = NewVertex;
			NewVertex->right = tmp->right;

			if (tree->root == tmp)
			{
				tree->root = NewVertex;
			}

			delete tmp;

			while (NewVertex != NULL)
			{
				NewVertex->height = Max_Height(NewVertex) + 1;
				Balance(tree, NewVertex);
				NewVertex = NewVertex->parent;
			}
		}
		else
		{
			while (NewVertex->right != NULL)
			{
				NewVertex = NewVertex->right;
			}

			Leaf* NewBalance = NewVertex->parent;

			NewVertex->parent->right = NewVertex->left;

			if (NewVertex->left != NULL)
			{
				NewVertex->left->parent = NewVertex->parent;
			}

			NewVertex->left = NULL;
			NewVertex->parent = NULL;
			tmp->left->parent = NULL;
			tmp->right->parent = NULL;
			tmp->right->parent = NewVertex;
			tmp->left->parent = NewVertex;
			NewVertex->right = tmp->right;
			NewVertex->left = tmp->left;
			tmp->left = tmp->right = NULL;
			NewVertex->parent = tmp->parent;

			if (tmp->parent != NULL)
			{
				if (tmp->parent->right == tmp)
				{
					tmp->parent->right = NewVertex;
				}
				else if (tmp->parent->left == tmp)
				{
					tmp->parent->left = NewVertex;
				}
			}

			if (tree->root == tmp)
			{
				tree->root = NewVertex;
			}

			delete tmp;

			while (NewBalance != NULL)
			{
				NewBalance->height = Max_Height(NewBalance) + 1;
				Balance(tree, NewBalance);
				NewBalance = NewBalance->parent;
			}
		}
	}
}

bool balance_tree(Leaf* leaf, int& height)
{	
	if ((leaf->left == NULL) && (leaf->right == NULL))
	{
		height = 0;
		return true;
	}
	else
	{
		if (leaf->right != NULL)
		{
			balance_tree(leaf->right, leaf->right->height);
		}
		if (leaf->left != NULL)
		{
			balance_tree(leaf->left, leaf->left->height);
		}

		leaf->height = Max_Height(leaf) + 1;

		if (abs(balance_leaf(leaf)) <= 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

int& get_height(Tree* tree)
{
	return tree->root->height;
}
