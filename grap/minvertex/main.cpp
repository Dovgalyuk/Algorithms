#include <locale>
#include <iostream>

#include "../Graphs/graph.h"
#include "../Graphs/graph.cpp"
#include "../Graphs/list.cpp"

using namespace std;

//�������� ��������(����������� ����)
void minimWay(Graph graph, unsigned int vertex) {
	//��������� �������������
	unsigned int sizeGraph = graph.sizeGraph();			//������ �����
	vector<bool> visitVertex(sizeGraph, 0);				//���������� �������
	vector<vector<unsigned int>> minWay(sizeGraph);		//���������� ����
	//���������� ���� ���������, ����� ��������, ����������� ������� ��������
	for (unsigned int i = 0; i < sizeGraph; i++) {
		if (graph.vertexList[i] != vertex) {
			graph.addLabelVertex(graph.vertexList[i], UINT_MAX);
		}
		else {
			graph.addLabelVertex(graph.vertexList[i], 0);
		}
	}

	//�������� ����
	unsigned int vertexMinLabel;
	unsigned int valueVertexMinLabel;
	for (unsigned int i = 0; i < sizeGraph; i++) {
		//����� �� ���������� ������� � ���������� ��������� �����
		valueVertexMinLabel = UINT_MAX;
		for (unsigned int j = 0; j < sizeGraph;j++) {
			if (visitVertex[graph.posVertex(graph.vertexList[j])] == 0 && graph.readLabelVertex(graph.vertexList[j]) < valueVertexMinLabel) {
				vertexMinLabel = graph.vertexList[j];
				valueVertexMinLabel = graph.readLabelVertex(graph.vertexList[j]);
			}
		}
		visitVertex[graph.posVertex(vertexMinLabel)] = 1;

		//������� ���� �������� ������ � �������
		for (ListItem* item = list_first(graph.adjacencyList[graph.posVertex(vertexMinLabel)]); item != NULL; item = list_item_next(item)) {
			if (graph.labelVertex[graph.posVertex(list_item_data(item))] > graph.labelVertex[graph.posVertex(vertexMinLabel)] + graph.labelEdge[graph.posVertex(vertexMinLabel)][graph.posVertex(list_item_data(item))]) {
				bool markNewMinWay = false;
				if (graph.labelVertex[graph.posVertex(list_item_data(item))] != UINT_MAX) {
					markNewMinWay = true;
				}
				graph.labelVertex[graph.posVertex(list_item_data(item))] = graph.labelVertex[graph.posVertex(vertexMinLabel)] + graph.labelEdge[graph.posVertex(vertexMinLabel)][graph.posVertex(list_item_data(item))];
				if (markNewMinWay == true) {
					minWay[graph.posVertex(list_item_data(item))].clear();
				}
				for (unsigned int j = 0; j < minWay[graph.posVertex(vertexMinLabel)].size(); j++) {
					minWay[graph.posVertex(list_item_data(item))].push_back(minWay[graph.posVertex(vertexMinLabel)][j]);
				}
				minWay[graph.posVertex(list_item_data(item))].push_back(vertexMinLabel);
			}
		}
	}

	//����� �����������
	for (unsigned int i = 0; i < sizeGraph; i++) {
		if (graph.vertexList[i] != vertex) {
			if (graph.labelVertex[i] != UINT_MAX) {
				cout << "����� ���� �� " << vertex << " �� " << graph.vertexList[i] << " = " << graph.labelVertex[i] << ". ����: ";
				for (unsigned int j = 0; j < minWay[i].size(); j++) {
					cout << minWay[i][j] << "->";
				}
				cout << graph.vertexList[i] << endl;
			}
			else {
				cout << "���� �� " << vertex << " �� " << graph.vertexList[i] << " �� ����������." << endl;
			}
		}
	}
}

//������� �������
void main() {
	setlocale(LC_ALL, "Russian");

	//������������� �����
	cout << "��������� ������������� �����" << endl;
	cout << "������� ���������� ������ �����: ";
	Graph graph;						//������ ����
	unsigned int vertex;				//����� �������

	//������ ����������� ��� ����������������� �����
	unsigned int numVertex;				//���-�� ������ � �����
	cin >> numVertex;
	for (unsigned int i = 0; i < numVertex; i++) {
		cout << "������� ����� ��� ����� �������: ";
		cin >> vertex;
		graph.addVertex(vertex);
	}

	//������ �����
	/*graph.addVertex(1);
	graph.addVertex(2);
	graph.addVertex(3);
	graph.addVertex(4);
	graph.addVertex(5);
	graph.addEdge(1, 2, 1);
	graph.addEdge(1, 3, 5);
	graph.addEdge(1, 5, 9);
	graph.addEdge(2, 3, 3);
	graph.addEdge(4, 3, 8);
	graph.addEdge(5, 2, 3);
	graph.addEdge(5, 3, 11);
	graph.addEdge(5, 4, 4);*/

	//����
	unsigned int numItemMenu;	//����� � ����
	unsigned int firstVertex;	//�������� ������� �����
	unsigned int secondVertex;	//�������� ������� �����
	unsigned int valueEdge;		//�������� ����� �����
	for (;;) {
		system("cls");
		cout << "������������� ����� � ���� ������� ���������:" << endl;
		graph.printGraph();
		cout << endl;
		cout << "����" << endl;
		cout << "1. �������� �������." << endl;
		cout << "2. ������� �������." << endl;
		cout << "3. �������� �����." << endl;
		cout << "4. ������� �����" << endl;
		cout << "5. ��������� ����� �� ������������� � �����." << endl;
		cout << "6. ����� ���������� ���� �� ����� ������� �� ���� ������." << endl;
		cout << "7. �����." << endl;
		cout << ">";
		cin >> numItemMenu;
		switch (numItemMenu)
		{
		case 1:
			cout << "������� ����� ��� ����� �������: ";
			cin >> vertex;
			graph.addVertex(vertex);
			system("pause");
			break;
		case 2:
			cout << "������� ����� ������� ��� ��������: ";
			cin >> vertex;
			graph.removeVertex(vertex);
			system("pause");
			break;
		case 3:
			cout << "�������� �������: ";
			cin >> firstVertex;
			cout << "�������� �������: ";
			cin >> secondVertex;
			cout << "����� ��� ������� �����: ";
			cin >> valueEdge;
			graph.addEdge(firstVertex, secondVertex, valueEdge);
			system("pause");
			break;
		case 4:
			cout << "�������� �������: ";
			cin >> firstVertex;
			cout << "�������� �������: ";
			cin >> secondVertex;
			graph.removeEdge(firstVertex, secondVertex);
			system("pause");
			break;
		case 5:
			cout << "�������� �������: ";
			cin >> firstVertex;
			cout << "�������� �������: ";
			cin >> secondVertex;
			graph.existEdge(firstVertex, secondVertex);
			system("pause");
			break;
		case 6:
			cout << "�������� �������: ";
			cin >> vertex;
			minimWay(graph, vertex);
			system("pause");
			break;
		case 7:
			return;
		}
	}
}