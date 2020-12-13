#include <iostream>

#include "node.h"

using namespace std;

//���������� ���� � ������
struct Node *addNode(Node *tree, string *str) {
	if (tree == NULL) {								//���� ���� ���, �� ������� ����� ���� �� ������� str
		tree = (Node*)malloc(sizeof(Node));
		tree->key = str;
		tree->left = NULL;
		tree->right = NULL;
		tree->height = 1;
	}
	else {
		if (str < tree->key) {						//���� ������ ������ �������� ����, �� ��� �����
			tree->left = addNode(tree->left, str);
		}
		else if (str > tree->key) {					//���� ������ ������ �������� ����, �� ��� ������
			tree->right = addNode(tree->right, str);
		}
	}
	return balanceAVLTree(tree);					//������ ������������
}

//����� ����
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

//�������� ����
struct Node *deleteNode(Node *tree, string *str) {
	if (tree != NULL)
	{
		if (tree == NULL) {
			return false;
		}
		if (str < tree->key) {								//���� ������ ������ �������� ����, �� ��� �����
			tree->left = deleteNode(tree->left, str);
		}
		else if (str > tree->key) {							//���� ������ ������ �������� ����, �� ��� ������
			tree->right = deleteNode(tree->right, str);
		}
		else {												//���� ������ ����� �������� ����(�������), �� �������
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
	return false;
}

//����� ���� � ����������� ������
Node* findMinNode(Node * tree)
{
	if (tree->left) {
		return findMinNode(tree->left);
	}
	else {
		return tree;
	}
}

//�������� ���� � ����������� ������
Node* deleteMinNode(Node * tree)
{
	if (tree->left == NULL)
		return tree->right;
	tree->left = deleteMinNode(tree->left);
	return balanceAVLTree(tree);
}

//������������ ������
Node* balanceAVLTree(Node* node)
{
	countHeight(node);
	if (balanceTree(node) == 2)						//���� ������ ����� 2, �� ������ ������������
	{
		if (balanceTree(node->right) < 0)
			node->right = turnRight(node->right);
		return turnLeft(node);
	}
	if (balanceTree(node) == -2)					//���� ������ ����� -2, �� ������ ������������
	{
		if (balanceTree(node->left) > 0)
			node->left = turnLeft(node->left);
		return turnRight(node);
	}
	balanceTree(node);
	return node;
}

//������ ����
unsigned char height(Node* node)
{
	if (node != NULL) {
		return node->height;
	}
	else {
		return 0;
	}
}

//������� ������ ����� ������
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

//������ ������
int balanceTree(Node* node)
{
	return height(node->right) - height(node->left);
}

//����� �������
Node* turnLeft(Node* leftNode)
{
	Node* rightNode = leftNode->right;
	leftNode->right = rightNode->left;
	rightNode->left = leftNode;
	countHeight(leftNode);
	countHeight(rightNode);
	return rightNode;
}

//������ �������
Node* turnRight(Node* rightNode)
{
	Node* leftNode = rightNode->left;
	rightNode->left = leftNode->right;
	leftNode->right = rightNode;
	countHeight(rightNode);
	countHeight(leftNode);
	return leftNode;
}