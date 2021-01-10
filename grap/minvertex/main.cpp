#include <locale>
#include <iostream>
-finput-charset=cp866 -fexec-charset=utf-8
#include "../Graphs/graph.h"
#include "../Graphs/graph.cpp"
#include "../Graphs/list.cpp"

using namespace std;

void minimWay(Graph graph, unsigned int vertex) {
	if (graph.posVertex(vertex) == -1) {
		cout << "versh otsutstvuet." << endl;
		return;
	}
	unsigned int sizeGraph = graph.sizeGraph();			
	vector<bool> visitVertex(sizeGraph, 0);			
	vector<vector<unsigned int>> minWay(sizeGraph);		
	
		graph.addLabelVertex(vertex, 0);
	for (unsigned int numVertex = 0; numVertex < sizeGraph;numVertex++) {
		if (graph.vertexGraph(numVertex) != vertex) {
		graph.addLabelVertex(graph.vertexGraph(numVertex), UINT_MAX);
		}
	}
	unsigned int vertexMinLabel;
	unsigned int valueVertexMinLabel;
	for (unsigned int numVertex = 0; numVertex < sizeGraph; numVertex++) {
		valueVertexMinLabel = UINT_MAX;
		for (unsigned int j = 0; j < sizeGraph;j++) {
			if (visitVertex[j] == 0 && graph.readLabelVertex(graph.vertexGraph(j)) < valueVertexMinLabel) {
				vertexMinLabel = graph.vertexGraph(j);
				valueVertexMinLabel = graph.readLabelVertex(graph.verteGraph(j));
			}
		}
		visitVertex[graph.posVertex(vertexMinLabel)] = 1;

		for (List<ListItem>::Iterator iter = graph.firstNeighborVertex(vertexMinLabel); iter != NULL; iter++) {
			if (graph.readlabelVertex((*iter)[0]) > graph.readlabelVertex(vertexMinLabel) + (*iter)[1]) {
				bool markNewMinWay = false;
				if (graph.readlabelVertex((*iter)[0])!= UINT_MAX) {
					markNewMinWay = true;
				}
				graph.addlabelVertex((*iter)[0] , graph.readlabelVertex(vertexMinLabel) +((*iter)[1])];
				if (markNewMinWay == true) {
					minWay[graph.posVertex((*iter)[0])].clear();
				}
				for (unsigned int j = 0; j < minWay[graph.posVertex(vertexMinLabel)].size(); j++) {
					minWay[graph.posVertex((*iter)[0])].push_back(minWay[graph.posVertex(vertexMinLabel)][j]);
				}
				minWay[graph.posVertex(list_item_data(item)[0])].push_back(vertexMinLabel);
			}
		}
	    }
	}

	for (unsigned int i = 0; i < sizeGraph; i++) {
		if (graph.vertexList[i] != vertex) {
			if (graph.readlabelVertex(graph.vertexGraph(i))!= UINT_MAX) {
				cout << "Äëèíà ïóòè îò " << vertex << " äî " << graph.vertexGraph[i] << " = " << graph.readlabelVertex(graph.vertexGraph(i)) << ". Ïóòü: ";
				for (unsigned int j = 0; j < minWay[i].size(); j++) {
					cout << minWay[i][j] << "->";
				}
				cout << graph.vertexGraph[i] << endl;
			}
			else {
				cout << "Ïóòè îò " << vertex << " äî " << graph.vertexGraph[i] << " íå ñóùåñòâóåò." << endl;
			}
		}
	}
}

void main() {
	setlocale(LC_ALL, "Russian");

	cout << "initialising graph" << endl;
	cout << "kol-vo vershin in graph: ";
	Graph graph;						
	unsigned int vertex;				
        graph.addVertex(1);
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

	//Ìåíþ
	unsigned int numItemMenu;	
	unsigned int firstVertex;	
	unsigned int secondVertex;	
	unsigned int valueEdge;		
	for (;;) {
		system("cls");
		cout << "graph matr smegnosti:" << endl;
		graph.printGraph();
		cout << endl;
		cout << "ÌÅÍÞ" << endl;
		cout << "1. add versh." << endl;
		cout << "2. delete versh." << endl;
		cout << "3. add rebro." << endl;
		cout << "4. delete rebro" << endl;
		cout << "5. proverka sushestvovania." << endl;
		cout << "6. krath put ot vershini do drugih." << endl;
		cout << "7. exit." << endl;
		cout << ">";
		cin >> numItemMenu;
		switch (numItemMenu)
		{
		case 1:
			cout << "vvedite nomer novoy vershini: ";
			cin >> vertex;
			if(graph.addVertex(vertex)){
		        cout << "vershina add." << endl;
			}
			else {
			cout << "vershina est." << endl;
			}
			system("pause");
			break;
		case 2:
			cout << "vvedite nomer dla udalenia: ";
			cin >> vertex;
			if(graph.removeVertex(vertex)){
				cout << "vershina udalena." << endl;
			}
			else {
				cout << "vershina otsutstvuet." << endl;
			}
			system("pause");
			break;
		case 3:
			cout << "ishodnaya vershina: ";
			cin >> firstVertex;
			cout << "konechnaya vershina: ";
			cin >> secondVertex;
			cout << "metka dla dannogo rebra: ";
			cin >> valueEdge;
			if (graph.addEdge(firstVertex, secondVertex, valueEdge)){
				 cout << "rebro meshdu vershinami add." << endl;
			}
			else {
				cout << "rebro meshdu vershinami uze est." << endl;
			}
			system("pause");
			break;
		case 4:
			cout << "ishodnaya vershina: ";
			cin >> firstVertex;
			cout << "konechnaya vershina: ";
			cin >> secondVertex;
		 if (graph.removeEdge(firstVertex, secondVertex)){
			 cout << "rebro meshdu vershinami delete." << endl;
			}
			else {
				cout << "rebro meshdu vershinami otsutstvuet." << endl;
			}
			system("pause");
			break;
		case 5:
			cout << "ishodnaya vershina: ";
			cin >> firstVertex;
			cout << "konechnaya vershina: ";
			cin >> secondVertex;
		if (graph.existEdge(firstVertex, secondVertex)){
			cout << "rebro meshdu vershinami est." << endl;
			}
			else {
				cout << "rebro meshdu vershinami otsutstvuet." << endl;
			}
			system("pause");
			break;
		case 6:
			cout << "ishodnaya vershina: ";
			cin >> vertex;
			minimWay(graph, vertex);
			system("pause");
			break;
		case 7:
			return;
		}
	}
}
