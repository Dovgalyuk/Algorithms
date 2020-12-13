#ifndef INTERFACE_H
#define INTERFACE_H

#include "node.h"

//1. ИНТЕРФЕЙС
class Interface {
private:
	Node *root;

public:
	Interface() {				//Конструктор
		root = NULL;
	}
	virtual ~Interface() {}		//Деструктор

	//Функции
	virtual void addValue(string*) {};			//Добавление значения
	virtual bool findValue(string*) = 0;		//Поиск значения. True - если удалось найти.
	virtual bool deleteValue(string*) = 0;		//Удаление значения True - если удалось удалить.
};

#endif