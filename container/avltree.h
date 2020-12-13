#ifndef AVLTREE_H
#define AVLTREE_H

#include "interface.h"

// 2. КОНТЕЙНЕР НА ОСНОВЕ АВЛ-ДЕРЕВА
class AVLTree : public Interface {
private:
	Node *root;	//Корень

public:
	AVLTree() {				//Конструтор
		root = NULL;
	}
	virtual ~AVLTree() {}	//Деструктор

	//Конкретизация методов интерфейса для данного класса
	//Добавление значения в контейнер
	virtual void addValue(string *str) {
		root = addNode(root, str);
	};

	//Поиск значения в контейнере. True - если удалось найти.
	virtual bool findValue(string *str) {
		return findNode(root, str);
	};

	//Удаление значения из контейнера. True - если удалось удалить.
	virtual bool deleteValue(string *str) {
		if (deleteNode(root, str) == 0)
			return false;
		return true;
	};
};

#endif