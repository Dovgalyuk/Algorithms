#include "graph.h"
#include <iostream>

using namespace std;

typedef Graph<string, int> MyGraph;

int main() {
	MyGraph* graph = new MyGraph;

	if (!graph) {
		cout << "Graph creation error\n";
		return 1;
	}

	string city1 = "Ohona";
	string city2 = "Pestovo";
	string city3 = "Novgorod";

	string label1 = "Haval";
	string label2= "Vesta";
	string label3 = "Volga";

	graph->add_vertex(city1, label1);
	graph->add_vertex(city2, label2);
	graph->add_vertex(city3, label3);

	if (graph->vertex_count() != 3) {
		cout << "Add_vertex error\n";
		return 1;
	}

	int road1 = 100;
	int road2 = 200;
	graph->add_edge(city1, city2, road1);
	graph->add_edge(city2, city3, road2);

	if (!graph->edge_exists(city1, city2)) {
		cout << "Add_edge error\n";
		return 1;
	}

	string test;
	graph->get_vertex_label(city1, test);
	if (test != "Haval") {
		cout << "Get_vertex_label error\n";
		return 1;
	}

	graph->remove_edge(city1, city2);
	if (graph->edge_exists(city1, city2))
	{
		cout << "Remove_edge error\n";
		return 1;
	}

	MyGraph copy(*graph);

	cout << "Vershini graph: ";
	for (size_t i = 0; i < graph->vertex_count(); i++) {
		cout << graph->vertex_name(i) << " ";
	}

	delete graph;
}