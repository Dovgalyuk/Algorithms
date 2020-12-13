#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

//��������� ���� ���-������
struct Node {
	string* key;
	struct Node* left;
	struct Node* right;
	unsigned char height;
};

//�������
Node* addNode(Node *tree, string *str);		//���������� ���� � ������
bool findNode(Node *tree, string *str);		//����� ����
Node* deleteNode(Node *tree, string *str);	//�������� ����

Node* findMinNode(Node *tree);				//����� ���� � ����������� ������
Node* deleteMinNode(Node *tree);				//�������� ���� � ����������� ������


//3. ������������ ���-������
Node* balanceAVLTree(Node* node);					//������������ ����
unsigned char height(Node* node);					//������� ������ ����� ������
void countHeight(Node* node);						//������� ������ ����
int balanceTree(Node* node);						//������ ������
Node* turnLeft(Node* leftNode);						//����� �������
Node* turnRight(Node* rightNode);					//������ �������

#endif