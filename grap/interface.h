#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include "list.h"

using namespace std;

//1. ���������
class Interface {
public:
	vector <unsigned int> vertexList;				//������ ������ �����
	vector <List*> adjacencyList;					//������ ���������
	vector <unsigned int> labelVertex;				//����� ������
	vector <vector<unsigned int>> labelEdge;		//����� ����


	Interface() {}									//�����������
	virtual ~Interface() {}							//���������� 

	//�������
	virtual unsigned int sizeGraph() = 0;								//������ �����
	virtual void printGraph() {};										//����� �����
	virtual void addVertex() {};										//�������� �������
	virtual void removeVertex() {};										//������� �������
	virtual void addEdge() {};											//�������� �����
	virtual void removeEdge() {};										//������� �����
	virtual void existEdge() {};										//�������� �� ������������� �����
	virtual void addLabelVertex() {};									//������ ����� �������
	virtual unsigned int readLabelVertex(unsigned int) = 0;				//������� ����� �������
	virtual void addLabelEdge() {};										//������ ����� �����
	virtual unsigned int readLabelEdge(unsigned int, unsigned int) = 0;	//������� ����� �����
};

#endif