#include "avltree.h"
#include <iostream>

struct AvlNode
{
	Data data;
	AvlNode* left;
	AvlNode* right;
	int height;
};

Data node_data(AvlNode* node)
{
	return node->data;
}

AvlNode* node_create(const Data& data)
{
	AvlNode* node = new AvlNode;
	node->data = data;
	node->left = nullptr;
	node->right = nullptr;
	node->height = 0;
	return node;
}

//private:
int avl_max(int val1, int val2)
{
	return val1 > val2 ? val1 : val2;
}

bool node_isBalanced(AvlNode* node, int& height)
{
	if (node == nullptr)
	{
		height = 0;
		return true;
	}
	else
	{
		int leftNodeHeight = 0;
		int rightNodeHeight = 0;

		bool isLeftBalanced = node_isBalanced(node->left, leftNodeHeight);
		bool isRightBalanced = node_isBalanced(node->right, rightNodeHeight);

		height = avl_max(leftNodeHeight, rightNodeHeight) + 1;

		return (std::abs(leftNodeHeight - rightNodeHeight) != 2) && isLeftBalanced && isRightBalanced;
	}
}

Data delete_min(AvlNode*& node)
{
	Data data;
	if (node->left == nullptr)
	{
		AvlNode* d = node;
		data = node->data;
		delete d;
		node = nullptr;
		return data;
	}
	else
	{
		data = delete_min(node->left);
		return data;
	}
}

AvlNode* srl(AvlNode* node)
{
	AvlNode* newnode;
	newnode = node->left;
	node->left = newnode->right;
	newnode->right = node;
	node->height = avl_max(node_baseheight(node->left), node_baseheight(node->right)) + 1;
	newnode->height = avl_max(node_baseheight(newnode->left), node->height) + 1;
	return newnode;
}

AvlNode* srr(AvlNode* node)
{
	AvlNode* newnode;
	newnode = node->right;
	node->right = newnode->left;
	newnode->left = node;
	node->height = avl_max(node_baseheight(node->left), node_baseheight(node->right)) + 1;
	newnode->height = avl_max(node->height, node_baseheight(newnode->right)) + 1;
	return newnode;
}

AvlNode* drl(AvlNode* node)
{
	node->left = srr(node->left);
	return srl(node);
}

AvlNode* drr(AvlNode* node)
{
	node->right = srl(node->right);
	return srr(node);
}


//

//public:

int node_baseheight(const AvlNode* node)
{
	return node == nullptr ? -1 : node->height;
}

void avl_insert(const Data& data, AvlNode*& node)
{
	if (node == nullptr) node = node_create(data);
	else
	{
		if (data < node->data)
		{
			avl_insert(data, node->left);
			if (node_baseheight(node->left) - node_baseheight(node->right) == 2)
			{
				if (data < node->left->data)
				{
					node = srl(node);
				}
				else
				{
					node = drl(node);
				}
			}
		}
		else if (data > node->data)
		{
			avl_insert(data, node->right);
			if (node_baseheight(node->right) - node_baseheight(node->left) == 2)
			{
				if (data > node->right->data)
				{
					node = srr(node);
				}
				else
				{
					node = drr(node);
				}
			}
		}
		else
		{
			//std::cerr << "element exists";
		}
	}
	int m, n, d;
	m = node_baseheight(node->left);
	n = node_baseheight(node->right);
	d = avl_max(m, n);
	(*node).height = d + 1;
#ifdef DEBUG
	int height = 0;
	std::cout << (node_isBalanced(node, height) ? "Balanced" : "Not balanced") << std::endl;
#endif
}

bool avl_remove(const Data& data, AvlNode*& node)
{
	if (node == nullptr) return false; //
	else if (data < node->data)
	{
		return avl_remove(data, node->left);
	}
	else if (data > node->data)
	{
		return avl_remove(data, node->right);
	}
	else if ((node->left == nullptr) && (node->right == nullptr))
	{
		delete node;
		node = nullptr;
	}
	else if (node->left == nullptr)
	{
		AvlNode* d = node->right;
		delete node;
		node = d;
	}
	else if (node->right == nullptr)
	{
		AvlNode* d = node->left;
		delete node;
		node = d;
	}
	else
	{
		node->data = delete_min(node->right);
	}
#ifdef DEBUG
	int height = 0;
	std::cout << (node_isBalanced(node, height) ? "Balanced" : "Not balanced") << std::endl;
#endif
	return true;
}

AvlNode* avl_find(const Data& data, AvlNode* node)
{
	if (node == nullptr)
		return NULL; //
	else
	{
		if (data == node->data) return node;
		if (data < node->data)
		{
			return avl_find(data, node->left);
		}
		else
		{
			return avl_find(data, node->right);
		}
	}
}

void avl_delete(AvlNode*& root)
{
	AvlNode* d;
	if (root != nullptr)
	{
		avl_delete(root->left);
		avl_delete(root->right);
		d = root;
		delete d;
		root = nullptr;
	}
}

void avl_inorder_print(AvlNode* node)
{
	if (node != nullptr)
	{
		avl_inorder_print(node->left);
		std::cout << node->data << std::endl;
		avl_inorder_print(node->right);
	}
}

