#ifndef AVLTREE_H
#define AVLTREE_H

#include "interface.h"

// 2. ÊÎÍÒÅÉÍÅÐ ÍÀ ÎÑÍÎÂÅ ÀÂË-ÄÅÐÅÂÀ
class AVLTree : public Interface {
private:
	Node *root;	//Êîðåíü

public:
	AVLTree() {				//Êîíñòðóòîð
		root = NULL;
	}
	virtual ~AVLTree() {}	//Äåñòðóêòîð

	//Êîíêðåòèçàöèÿ ìåòîäîâ èíòåðôåéñà äëÿ äàííîãî êëàññà
	//Äîáàâëåíèå çíà÷åíèÿ â êîíòåéíåð
	virtual void addValue(string *str) {
		root = addNode(root, str);
	};

	//Ïîèñê çíà÷åíèÿ â êîíòåéíåðå. True - åñëè óäàëîñü íàéòè.
	virtual bool findValue(string *str) {
		return findNode(root, str);
	};

	//Óäàëåíèå çíà÷åíèÿ èç êîíòåéíåðà. True - åñëè óäàëîñü óäàëèòü.
	virtual bool deleteValue(string *str) {
		if (deleteNode(root, str) == 0)
			return false;
		return true;
		}
		else {
			balanceAVLTree(root);	//Балансировка дерева
			return true;
		}
	};
};

#endif
