#ifndef INTERFACE_H
#define INTERFACE_H

#include "node.h"

//1. ���������
class Interface {
private:
	Node *root;

public:
	Interface() {				//�����������
		root = NULL;
	}
	virtual ~Interface() {}		//����������

	//�������
	virtual void addValue(string*) {};			//���������� ��������
	virtual bool findValue(string*) = 0;		//����� ��������. True - ���� ������� �����.
	virtual bool deleteValue(string*) = 0;		//�������� �������� True - ���� ������� �������.
};

#endif