#include "AVLtree.h"

struct binaryTree
{
	binaryTree* leftElem;
	binaryTree* rightElem;
	Key key;
	Data data;
	int8_t nodeHeight;
};

binaryTree* createBinTree(const Key& key, const Data& value)
{
	binaryTree* root = new binaryTree;
	root->leftElem = nullptr;
	root->rightElem = nullptr;
	root->key = key;
	root->data = value;
	root->nodeHeight = 1;

	return root;
}

int8_t nodeHeight(binaryTree* node)
{
	return node ? node->nodeHeight : 0;
}

int8_t nodeMaxHeight(int8_t nodeHeightLeft, int8_t nodeHeightRight)
{
	return nodeHeightLeft > nodeHeightRight ? nodeHeightLeft : nodeHeightRight;
}

int8_t getNodeBalance(binaryTree* node)
{
	return nodeHeight(node->leftElem) - nodeHeight(node->rightElem);
}

void correctNodeHeight(binaryTree* node)
{
	node->nodeHeight = nodeMaxHeight(nodeHeight(node->leftElem), nodeHeight(node->rightElem)) + 1;
}

binaryTree* smallLeftRotate(binaryTree* node)
{
	binaryTree* b = node->rightElem;
	node->rightElem = b->leftElem;
	b->leftElem = node;
	correctNodeHeight(node);
	correctNodeHeight(b);

	return b;
}

binaryTree* smallRightRotate(binaryTree* node)
{
	binaryTree* b = node->leftElem;
	node->leftElem = b->rightElem;
	b->rightElem = node;
	correctNodeHeight(node);
	correctNodeHeight(b);

	return b;
}

binaryTree* bigLeftRotate(binaryTree* node)
{
	node->rightElem = smallRightRotate(node->rightElem);
	return smallLeftRotate(node);
}

binaryTree* bigRightRotate(binaryTree* node)
{
	node->leftElem = smallLeftRotate(node->leftElem);
	return smallRightRotate(node);
}

binaryTree* AVLbalance(binaryTree* node)
{
	node->nodeHeight = nodeMaxHeight(nodeHeight(node->leftElem), nodeHeight(node->rightElem)) + 1;

	if (getNodeBalance(node) == -2)
	{
		if (getNodeBalance(node->rightElem) > 0)
		{
			return bigLeftRotate(node);
		}
		else
		{
			return smallLeftRotate(node);
		}
	}
	else if (getNodeBalance(node) == 2)
	{
		if (getNodeBalance(node->leftElem) < 0)
		{
			return bigRightRotate(node);
		}
		else
		{
			return smallRightRotate(node);
		}
	}

	return node;

}

binaryTree* insertElem(binaryTree* root, const Key& key, const Data& value)
{
	if (!root)
	{
		return createBinTree(key, value);
	}
	else
	{
		if (key < root->key)
		{
			root->leftElem = insertElem(root->leftElem, key, value);
		}
		else if (key > root->key)
		{
			root->rightElem = insertElem(root->rightElem, key, value);
		}
		else
		{
			root->data = value;
		}
	}
	return AVLbalance(root);
}

binaryTree* findParentOfMinNode(binaryTree* node)
{
	if (!node->leftElem)
	{
		return node;
	}

	binaryTree* leftChild = node->leftElem;

	if (!leftChild->leftElem)
	{
		return node;
	}
	return findParentOfMinNode(node->leftElem);
}

binaryTree* deleteElem(binaryTree* root, const Key& key)
{
	if (!root)
	{
		return nullptr;
	}
	else
	{
		if (key < root->key)
		{
			root->leftElem = deleteElem(root->leftElem, key);
		}
		else if (key > root->key)
		{
			root->rightElem = deleteElem(root->rightElem, key);
		}
		else
		{
			if (!root->leftElem && !root->rightElem)
			{
				delete root;
				return nullptr;
			}
			else if (!root->leftElem || !root->rightElem)
			{
				binaryTree* nextNode = root->leftElem ? root->leftElem : root->rightElem;
				delete root;
				return nextNode;
			}
			else
			{
				binaryTree* parentMinNode = findParentOfMinNode(root->rightElem);
				if (!parentMinNode->leftElem)
				{
					root->key = parentMinNode->key;
					root->data = parentMinNode->data;

					if (!parentMinNode->rightElem)
					{
						root->rightElem = nullptr;
					}
					else
					{
						root->rightElem = parentMinNode->rightElem;
					}
				}
				else
				{
					binaryTree* minNode = parentMinNode->leftElem;

					root->key = minNode->key;
					root->data = minNode->data;

					if (minNode->rightElem)
					{
						parentMinNode->leftElem = minNode->rightElem;
					}
					else
					{
						parentMinNode->leftElem = nullptr;
					}
				}
				delete parentMinNode->leftElem;
			}
		}
	}

	return AVLbalance(root);
}

binaryTree* findElem(binaryTree* root, const Key& key)
{
	if (!root)
	{
		return nullptr;
	}
	else if (root->key == key)
	{
		return root;
	}
	else
	{
		if (key < root->key)
		{
			return findElem(root->leftElem, key);
		}
		else
		{
			return findElem(root->rightElem, key);
		}
	}
}

binaryTree* deleteBinTree(binaryTree* root)
{
	if (root)
	{
		deleteBinTree(root->leftElem);
		deleteBinTree(root->rightElem);
		delete root;
	}
	return nullptr;
}


Data getTreeData(binaryTree* node)
{

	return node ? node->data : "";
}

void printBinTree(binaryTree* root, int offset)
{
	if (root)
	{
		printBinTree(root->rightElem, offset + 1);

		for (int i = 0; i < offset; i++)
		{
			std::cout << " ";
		}
		std::cout << root->data;

		printBinTree(root->leftElem, offset + 1);
	}
	else
	{
		std::cout << std::endl;
	}
}