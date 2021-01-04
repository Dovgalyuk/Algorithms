#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "interface.h"

class Graph :public Interface {
public:
	vector <unsigned int> vertexList;				//������ ������ �����
	vector <List*> adjacencyList;					//������ ���������
	vector <unsigned int> labelVertex;				//����� ������
	vector <vector<unsigned int>> labelEdge;		//����� ����

	//��������������� �������
	unsigned int posVertex(unsigned int vertex);	//�������� ������� ������� � ������

	//�����������
	Graph() {}
	//����������
	virtual ~Graph() {}

	//�������
	virtual unsigned int sizeGraph();																			//������ �����
	virtual void printGraph();																					//����� �����
	virtual void addVertex(unsigned int vertex);																//�������� �������
	virtual void removeVertex(unsigned int vertex);																//������� �������
	virtual void addEdge(unsigned int firstVertex, unsigned int secondVertex, unsigned int valueEdge);			//�������� �����
	virtual void removeEdge(unsigned int firstVertex, unsigned int secondVertex);								//������� �����
	virtual void existEdge(unsigned int firstVertex, unsigned int secondVertex);								//�������� �� ������������� �����
	virtual void addLabelVertex(unsigned int vertex, unsigned int valueVertex);									//������ ����� �������
	virtual unsigned int readLabelVertex(unsigned int vertex);													//������� ����� �������
	virtual void addLabelEdge(unsigned int firstVertex, unsigned int secondVertex, unsigned int valueEdge);		//������ ����� �����
	virtual unsigned int readLabelEdge(unsigned int firstVertex, unsigned int secondVertex);					//������� ����� �����
};

#endif