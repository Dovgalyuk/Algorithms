#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

//Ñòðóêòóðà óçëà ÀÂË-äåðåâà
struct Node {
	string* key;
	struct Node* left;
	struct Node* right;
	unsigned char height;
};

//Ôóíêöèè
Node* addNode(Node *tree, string *str);		//Äîáàâëåíèå óçëà â äåðåâî
bool findNode(Node *tree, string *str);		//Ïîèñê óçëà
Node* deleteNode(Node *tree, string *str);	//Óäàëåíèå óçëà

Node* findMinNode(Node *tree);				//Ïîèñê óçëà ñ ìèíèìàëüíûì êëþ÷îì
Node* deleteMinNode(Node *tree);				//Óäàëåíèå óçëà ñ ìèíèìàëüíûì êëþ÷îì


//3. ÁÀËÀÍÑÈÐÎÂÊÀ ÀÂË-ÄÅÐÅÂÀ
Node* balanceAVLTree(Node* node);					//Áàëàíñèðîâêà óçëà
unsigned char height(Node* node);					//Ïîäñ÷åò âûñîòû óçëîâ äåðåâà
void countHeight(Node* node);						//Ïîäñ÷åò âûñîòû óçëà
int balanceTree(Node* node);						//Áàëàíñ äåðåâà
Node* turnLeft(Node* leftNode);						//Ëåâûé ïîâîðîò
Node* turnRight(Node* rightNode);					//Ïðàâûé ïîâîðîò
unsigned char correctBalanceTree(Node* node);	//Обход дерева и пересчет высот.

#endif
