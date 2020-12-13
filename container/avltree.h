#ifndef AVLTREE_H
#define AVLTREE_H

#include "interface.h"

// 2. ��������� �� ������ ���-������
class AVLTree : public Interface {
private:
	Node *root;	//������

public:
	AVLTree() {				//����������
		root = NULL;
	}
	virtual ~AVLTree() {}	//����������

	//������������� ������� ���������� ��� ������� ������
	//���������� �������� � ���������
	virtual void addValue(string *str) {
		root = addNode(root, str);
	};

	//����� �������� � ����������. True - ���� ������� �����.
	virtual bool findValue(string *str) {
		return findNode(root, str);
	};

	//�������� �������� �� ����������. True - ���� ������� �������.
	virtual bool deleteValue(string *str) {
		if (deleteNode(root, str) == 0)
			return false;
		return true;
	};
};

#endif