#include "splaytree.h"
#include <iostream>

struct Node
{
	Key key;
	Data value;

	Node* pLeft;
	Node* pRight;
	Node* pParent;
};

enum  Direction
{
	LEFT,	//0
	RIGHT	//1
};

Direction operator !(Direction direction) { return direction == LEFT ? RIGHT : LEFT; }

Direction parent_direction(Node* node)
{ 
	if (node == node->pParent->pLeft)
		return LEFT;
	return RIGHT;
}

void node_right_rotate(Node* parent)
{
	Node* node = parent->pLeft;

	parent->pLeft = node->pRight;
	if (parent->pLeft != nullptr)
		parent->pLeft->pParent = parent;

	node->pRight = parent;
	node->pParent = parent->pParent;

	if (parent->pParent != nullptr)
	{
		if (parent_direction(parent) == LEFT)
			parent->pParent->pLeft = node;
		else
			parent->pParent->pRight = node;
	}
	parent->pParent = node;
}

void node_left_rotate(Node* parent)
{
	Node* node = parent->pRight;

	parent->pRight = node->pLeft;
	if (parent->pRight != nullptr)
		parent->pRight->pParent = parent;

	node->pLeft = parent;
	node->pParent = parent->pParent;

	if (parent->pParent != nullptr)
	{
		if (parent_direction(parent) == LEFT)
			parent->pParent->pLeft = node;
		else
			parent->pParent->pRight = node;
	}
	parent->pParent = node;
}

void node_left_right_rotate(Node* parent_2)
{
	//std::cout << "\tnode_left_right_rotate\n";
	Node* parent_1 = parent_2->pLeft;
	node_left_rotate(parent_1);
	node_right_rotate(parent_2);
}

void node_right_left_rotate(Node* parent_2)
{
	//std::cout << "\tnode_right_left_rotate\n";
	Node* parent_1 = parent_2->pRight;
	node_right_rotate(parent_1);
	node_left_rotate(parent_2);
}

void node_left_left_rotate(Node* parent_2)
{
	//std::cout << "\tnode_left_left_rotate\n";
	Node* parent_1 = parent_2->pRight;
	node_left_rotate(parent_2);
	node_left_rotate(parent_1);
}

void node_right_right_rotate(Node* parent_2)
{
	//std::cout << "\tnode_right_right_rotate\n";
	Node* parent_1 = parent_2->pLeft;
	node_right_rotate(parent_2);
	node_right_rotate (parent_1);
}



void splay(Node* node)
{
	static void (*big_rotate[4])(Node*) = {
		node_left_left_rotate,	//00 =0
		node_left_right_rotate,	//01 =1
		node_right_left_rotate,	//10 =2
		node_right_right_rotate	//11 =3
	};

	Direction direction_1, direction_2;
	for (Node* node_it; node->pParent != nullptr; )
	{
		direction_1 = parent_direction(node);
		node_it = node->pParent; 
		if (node_it->pParent == nullptr)
		{
			if (direction_1 == RIGHT)
			{
				//std::cout << "\tnode_left_rotate\n";
				node_left_rotate(node_it);
			}
			else
			{
				//std::cout << "\tnode_right_rotate\n";
				node_right_rotate(node_it);
			}
			return;  
		}

		direction_2 = parent_direction(node_it);
		node_it = node_it->pParent;

		big_rotate[ ( !direction_1 << 1) | !direction_2 ](node_it);
	}
	return;
}

void node_set(Node* node, const Key& key, const Data& value)
{
	node->key = key;
	node->value = value;
}

Data node_get_value(Node* node) { return node->value; }

Key node_get_key(Node* node) { return node->key; }

Node* node_create()
{
	Node* new_node = new Node;
	new_node->pLeft = nullptr;
	new_node->pRight = nullptr;
	new_node->pParent = nullptr;
	return new_node;
}

void tree_delete(Node* root)
{
	if (root->pLeft != nullptr)
		tree_delete(root->pLeft);
	if (root->pRight != nullptr)
		tree_delete(root->pRight);
	delete root;
}

Node* node_find(Node* root, const Key& key)
{
	if (root == nullptr)
		return nullptr;

	if (key < root->key)
		return node_find(root->pLeft, key);
	else if (key > root->key)
		return node_find(root->pRight, key);
	else
	{
		splay(root);
		return root;
	}
}

bool node_add(Node* root, Node* new_node)
{
	if (new_node->key < root->key)
	{
		if (root->pLeft == nullptr)
		{
			root->pLeft = new_node;
			new_node->pParent = root;
			return true;
		}
		return node_add(root->pLeft, new_node);
	}
	else if (new_node->key > root->key)
	{
		if (root->pRight == nullptr)
		{
			root->pRight = new_node;
			new_node->pParent = root;
			return true;
		}
		return node_add(root->pRight, new_node);
	}
	else
		return false;
}

Node* root_remove(Node* root)
{
	Node* new_root = nullptr;
	if (root->pLeft != nullptr)
	{
		new_root = root->pLeft;
		if (new_root->pRight == nullptr)
		{
			new_root->pParent = nullptr;
			new_root->pRight = root->pRight;
			if (root->pRight != nullptr)
				root->pRight->pParent = new_root;
		}
		else
		{
			for (new_root = new_root->pRight; new_root->pRight != nullptr; new_root = new_root->pRight);

			if (new_root->pLeft != nullptr)
				new_root->pLeft->pParent = new_root->pParent;
			new_root->pParent->pRight = new_root->pLeft;
			new_root->pParent = nullptr;

			new_root->pLeft = root->pLeft;
			root->pLeft->pParent = new_root;

			new_root->pRight = root->pRight;
			if (root->pRight != nullptr)
				root->pRight->pParent = new_root;
		}
	}
	else if (root->pRight != nullptr)
	{
		new_root = root->pRight;
		if (new_root->pLeft == nullptr)
			new_root->pParent = nullptr;
		else
		{
			for (new_root = new_root->pLeft; new_root->pLeft != nullptr; new_root = new_root->pLeft);

			if (new_root->pRight != nullptr)
				new_root->pRight->pParent = new_root->pParent;
			new_root->pParent->pLeft = new_root->pRight;
			new_root->pParent = nullptr;

			new_root->pRight = root->pRight;
			root->pRight->pParent = new_root;
		}
	}
	delete root;
	return new_root;
}

int tree_height(Node* root, int height =1)
{
	int left_height = 0, right_height = 0;
	if (root->pLeft != nullptr)
		left_height = tree_height(root->pLeft, height + 1);
	if (root->pRight != nullptr)
		right_height = tree_height(root->pRight, height + 1);

	int new_height = left_height > right_height ? left_height : right_height;

	return new_height != 0 ? new_height : height;
}

void print_tree(Node* root)//DEBUG
{
	if (root == nullptr)
		return;
	print_tree(root->pLeft);
	print_tree(root->pRight);
	std::cout
		<< "key =" << root->key
		<< "\tvalue =" << root->value
		<< "\tpLeft =" << (root->pLeft != nullptr ? root->pLeft->key : "NULL")
		<< "\tpRight =" << (root->pRight != nullptr ? root->pRight->key : "NULL")
		<< "\tpParent =" << (root->pParent != nullptr ? root->pParent->key : "NULL")
		<< std::endl;
}
