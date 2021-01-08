#include <locale>
#include <iostream>

#include "../Graphs/graph.h"
#include "../Graphs/graph.cpp"
#include "../Graphs/list.cpp"

using namespace std;

//Àëãîðèòì Äåéêñòðû(êðàò÷àéøåãî ïóòè)
void minimWay(Graph graph, unsigned int vertex) {
	//Íà÷àëüíàÿ èíèöèàëèçàöèÿ
	if (graph.posVertex(vertex) == -1) {
		cout << "Данная вершина не существует в графе." << endl;
		return;
	}
	unsigned int sizeGraph = graph.sizeGraph();			//Ðàçìåð ãðàôà
	vector<bool> visitVertex(sizeGraph, 0);				//Ïîñåùåííûå âåðøèíû
	vector<vector<unsigned int>> minWay(sizeGraph);		//Êðàò÷àéøèå ïóòè
	
	//Ïðèñâîåíèå âñåì ýëåìåíòàì, êðîìå èñõîäíîé, ìàêñèìàëüíî áîëüøîå çíà÷åíèå
		graph.addLabelVertex(vertex, 0);
	for (unsigned int numVertex = 0; numVertex < sizeGraph;numVertex++) {
		if (graph.vertexGraph(numVertex) != vertex) {
		graph.addLabelVertex(graph.vertexGraph(numVertex), UINT_MAX);
		}
	}
	//Îñíîâíîé öèêë
	unsigned int vertexMinLabel;
	unsigned int valueVertexMinLabel;
	for (unsigned int numVertex = 0; numVertex < sizeGraph; numVertex++) {
		//Âûáîð íå ïîñåùåííîé âåðøèíû ñ íàèìåíüøèì çíà÷åíèåì ìåòêè
		valueVertexMinLabel = UINT_MAX;
		for (unsigned int j = 0; j < sizeGraph;j++) {
			if (visitVertex[j] == 0 && graph.readLabelVertex(graph.vertexGraph(j)) < valueVertexMinLabel) {
				vertexMinLabel = graph.vertexGraph(j);
				valueVertexMinLabel = graph.readLabelVertex(graph.verteGraph(j));
			}
		}
		visitVertex[graph.posVertex(vertexMinLabel)] = 1;

		//Ïåðåáîð âñåõ ñîñåäíèõ âåðøèí è ïîäñ÷¸ò
		ListItem *item = NULL;
		for (item = graph.neighborsVertex(vertexMinLabel, item); item != NULL; item = graph.neighborsVertex(vertexMinLabel, item)) {
			if (graph.readlabelVertex(list_item_data(item)[0]) > graph.readlabelVertex(vertexMinLabel) + list_item_data(item)[1]) {
				bool markNewMinWay = false;
				if (graph.readlabelVertex(list_item_data(item)[0])!= UINT_MAX) {
					markNewMinWay = true;
				}
				graph.addlabelVertex(list_item_data(item)[0] , graph.readlabelVertex(vertexMinLabel) +(list_item_data(item)[1])];
				if (markNewMinWay == true) {
					minWay[graph.posVertex(list_item_data(item)[0])].clear();
				}
				for (unsigned int j = 0; j < minWay[graph.posVertex(vertexMinLabel)].size(); j++) {
					minWay[graph.posVertex(list_item_data(item)[0])].push_back(minWay[graph.posVertex(vertexMinLabel)][j]);
				}
				minWay[graph.posVertex(list_item_data(item)[0])].push_back(vertexMinLabel);
			}
		}
	}

	//Âûâîä ðåçóëüòàòîâ
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

//ÃËÀÂÍÀß ÔÓÍÊÖÈß
void main() {
	setlocale(LC_ALL, "Russian");

	//Èíèöèàëèçàöèÿ ãðàôà
	cout << "ÍÀ×ÀËÜÍÀß ÈÍÈÖÈÀËÈÇÀÖÈß ÃÐÀÔÀ" << endl;
	cout << "Ââåäèòå êîëè÷åñòâî âåðøèí ãðàôà: ";
	Graph graph;						//Ñîçäà¸ì ãðàô
	unsigned int vertex;				//Íîìåð âåðøèíû
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
	unsigned int numItemMenu;	//Ïóíêò â ìåíþ
	unsigned int firstVertex;	//Èñõîäíàÿ âåðøèíà ðåáðà
	unsigned int secondVertex;	//Êîíå÷íàÿ âåðøèíà ðåáðà
	unsigned int valueEdge;		//Çíà÷åíèå ìåòêè ðåáðà
	for (;;) {
		system("cls");
		cout << "ÏÐÅÄÑÒÀÂËÅÍÈÅ ÃÐÀÔÀ Â ÂÈÄÅ ÌÀÒÐÈÖÛ ÑÌÅÆÍÎÑÒÈ:" << endl;
		graph.printGraph();
		cout << endl;
		cout << "ÌÅÍÞ" << endl;
		cout << "1. Äîáàâèòü âåðøèíó." << endl;
		cout << "2. Óäàëèòü âåðøèíó." << endl;
		cout << "3. Äîáàâèòü ðåáðî." << endl;
		cout << "4. Óäàëèòü ðåáðî" << endl;
		cout << "5. Ïðîâåðèòü ðåáðî íà ñóùåñòâîâàíèå â ãðàôå." << endl;
		cout << "6. Íàéòè êðàò÷àéøèé ïóòü îò îäíîé âåðøèíû äî âñåõ äðóãèõ." << endl;
		cout << "7. Âûõîä." << endl;
		cout << ">";
		cin >> numItemMenu;
		switch (numItemMenu)
		{
		case 1:
			cout << "Ââåäèòå íîìåð äëÿ íîâîé âåðøèíû: ";
			cin >> vertex;
			graph.addVertex(vertex);
			system("pause");
			break;
		case 2:
			cout << "Ââåäèòå íîìåð âåðøèíû äëÿ óäàëåíèÿ: ";
			cin >> vertex;
			graph.removeVertex(vertex);
			system("pause");
			break;
		case 3:
			cout << "Èñõîäíàÿ âåðøèíà: ";
			cin >> firstVertex;
			cout << "Êîíå÷íàÿ âåðøèíà: ";
			cin >> secondVertex;
			cout << "Ìåòêà äëÿ äàííîãî ðåáðà: ";
			cin >> valueEdge;
			graph.addEdge(firstVertex, secondVertex, valueEdge);
			system("pause");
			break;
		case 4:
			cout << "Èñõîäíàÿ âåðøèíà: ";
			cin >> firstVertex;
			cout << "Êîíå÷íàÿ âåðøèíà: ";
			cin >> secondVertex;
			graph.removeEdge(firstVertex, secondVertex);
			system("pause");
			break;
		case 5:
			cout << "Èñõîäíàÿ âåðøèíà: ";
			cin >> firstVertex;
			cout << "Êîíå÷íàÿ âåðøèíà: ";
			cin >> secondVertex;
			graph.existEdge(firstVertex, secondVertex);
			system("pause");
			break;
		case 6:
			cout << "Èñõîäíàÿ âåðøèíà: ";
			cin >> vertex;
			minimWay(graph, vertex);
			system("pause");
			break;
		case 7:
			return;
		}
	}
}
