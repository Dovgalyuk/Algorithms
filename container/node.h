#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

//Структура узла АВЛ-дерева
struct Node {
	string* key;
	struct Node* left;
	struct Node* right;
	unsigned char height;
};

//Функции
Node* addNode(Node *tree, string *str);		//Добавление узла в дерево
bool findNode(Node *tree, string *str);		//Поиск узла
Node* deleteNode(Node *tree, string *str);	//Удаление узла

Node* findMinNode(Node *tree);				//Поиск узла с минимальным ключом
Node* deleteMinNode(Node *tree);				//Удаление узла с минимальным ключом


//3. БАЛАНСИРОВКА АВЛ-ДЕРЕВА
Node* balanceAVLTree(Node* node);					//Балансировка узла
unsigned char height(Node* node);					//Подсчет высоты узлов дерева
void countHeight(Node* node);						//Подсчет высоты узла
int balanceTree(Node* node);						//Баланс дерева
Node* turnLeft(Node* leftNode);						//Левый поворот
Node* turnRight(Node* rightNode);					//Правый поворот

#endif