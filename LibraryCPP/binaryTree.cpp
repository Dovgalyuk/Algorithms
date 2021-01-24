#include "binaryTree.h"

struct binaryTree
{
	binaryTree* leftElem;
	binaryTree* rightElem;
	Key key;
	Data data;
};

binaryTree* createBinTree(const Key& key, const Data& value)
{
	binaryTree* root = new binaryTree;
	root->leftElem = nullptr;
	root->rightElem = nullptr;
	root->key = key;
	root->data = value;

	return root;
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
	return root;
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
			else if(!root->leftElem || !root->rightElem)
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

	return root;
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