#include <iostream>

#include "node.h"

using namespace std;

//Äîáàâëåíèå óçëà â äåðåâî
struct Node *addNode(Node *tree, string *str) {
	if (tree == NULL) {								//Åñëè óçëà íåò, òî ñîçäàåì íîâûé óçåë ñî ñòðîêîé str
		tree = (Node*)malloc(sizeof(Node));
		tree->key = str;
		tree->left = NULL;
		tree->right = NULL;
		tree->height = 1;
	}
	else {
		if (str < tree->key) {						//Åñëè ñòðîêà ìåíüøå òåêóùåãî óçëà, òî èä¸ì âëåâî
			tree->left = addNode(tree->left, str);
		}
		else if (str > tree->key) {					//Åñëè ñòðîêà áîëüøå òåêóùåãî óçëà, òî èä¸ì âïðàâî
			tree->right = addNode(tree->right, str);
		}
	}
	return balanceAVLTree(tree);					//Äåëàåì áàëàíñèðîâêó
}

//Ïîèñê óçëà
bool findNode(Node *tree, string *str) {
	if (tree != NULL)
	{
		if (str == tree->key) {
			return true;
		}
		if (findNode(tree->left, str) == true) {
			return true;
		}
		if (findNode(tree->right, str) == true) {
			return true;
		}
	}
	return false;
}

//Óäàëåíèå óçëà
struct Node *deleteNode(Node *tree, string *str) {
	if (tree != NULL)
	{
		if (tree == NULL) {
			return false;
		}
		if (str < tree->key) {								//Åñëè ñòðîêà ìåíüøå òåêóùåãî óçëà, òî èä¸ì âëåâî
			tree->left = deleteNode(tree->left, str);
		}
		else if (str > tree->key) {							//Åñëè ñòðîêà áîëüøå òåêóùåãî óçëà, òî èä¸ì âïðàâî
			tree->right = deleteNode(tree->right, str);
		}
		else {												//Åñëè ñòðîêà ðàâíî òåêóùåìó óçëó(íàéäåíà), òî óäàëÿåì
			Node *leftNode = tree->left;
			Node *rightNode = tree->right;
			if (rightNode == NULL) {
				return leftNode;
			}

			Node *minNode = findMinNode(rightNode);
			minNode->right = deleteMinNode(rightNode);
			minNode->left = leftNode;
			return balanceAVLTree(minNode);
		}
	}
	return balanceAVLTree(tree);
}

//Ïîèñê óçëà ñ ìèíèìàëüíûì êëþ÷îì
Node* findMinNode(Node * tree)
{
	if (tree->left) {
		return findMinNode(tree->left);
	}
	else {
		return tree;
	}
}

//Óäàëåíèå óçëà ñ ìèíèìàëüíûì êëþ÷îì
Node* deleteMinNode(Node * tree)
{
	if (tree->left == NULL)
		return tree->right;
	tree->left = deleteMinNode(tree->left);
	return balanceAVLTree(tree);
}

//Áàëàíñèðîâêà äåðåâà
Node* balanceAVLTree(Node* node)
{
	countHeight(node);
	if (balanceTree(node) == 2)						//Åñëè áàëàíñ ðàâåí 2, òî äåëàåì áàëàíñèðîâêó
	{
		if (balanceTree(node->right) < 0)
			node->right = turnRight(node->right);
		return turnLeft(node);
	}
	if (balanceTree(node) == -2)					//Åñëè áàëàíñ ðàâåí -2, òî äåëàåì áàëàíñèðîâêó
	{
		if (balanceTree(node->left) > 0)
			node->left = turnLeft(node->left);
		return turnRight(node);
	}
	balanceTree(node);
	return node;
}

//Âûñîòà óçëà
unsigned char height(Node* node)
{
	if (node != NULL) {
		return node->height;
	}
	else {
		return 0;
	}
}

//Ïîäñ÷åò âûñîòû óçëîâ äåðåâà
void countHeight(Node* node)
{
	unsigned char heightLeft = height(node->left);
	unsigned char heightRight = height(node->right);
	if (heightLeft > heightRight) {
		node->height = heightLeft + 1;
	}
	else {
		node->height = heightRight + 1;
	}
}

//Áàëàíñ äåðåâà
int balanceTree(Node* node)
{
	return height(node->right) - height(node->left);
}

//Ëåâûé ïîâîðîò
Node* turnLeft(Node* leftNode)
{
	Node* rightNode = leftNode->right;
	leftNode->right = rightNode->left;
	rightNode->left = leftNode;
	countHeight(leftNode);
	countHeight(rightNode);
	return rightNode;
}

//Ïðàâûé ïîâîðîò
Node* turnRight(Node* rightNode)
{
	Node* leftNode = rightNode->left;
	rightNode->left = leftNode->right;
	leftNode->right = rightNode;
	countHeight(rightNode);
	countHeight(leftNode);
	return leftNode;
}

//Пересчёт высот узлов. 
unsigned char correctBalanceTree(Node* tree) {
	unsigned char left, right;
	if (tree != NULL) {
		if (tree->left != NULL) {
			left = correctBalanceTree(tree->left);
		}
		else {
			left = 0;
		}
		if (tree->right != NULL) {
			right = correctBalanceTree(tree->right);
		}
		else {
			right = 0;
		}
		if (left > right) {
			if (tree->height != left + 1) {
				cout << "ОШИБКА. Во время перепроверки дерева подсчитанная высота не совпадает с исходным." << endl;
			
		}
		else {
				if (tree->height! = right + 1) {
			cout << "ОШИБКА. Во время перепроверки дерева подсчитанная высота не совпадает с исходным." << endl;
				}
		}
		return tree->height;
	}
	return 0;
}
