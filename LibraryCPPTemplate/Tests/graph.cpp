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
	if (graph->edge_exists(city2, city1)) {
		cout << "Edge_exists (reverse) error\n";
		return 1;
	}
	if (graph->edge_exists(city1, city3)) {
		cout << "Edge_exists (non-existent) error\n";
		return 1;
	}




	string test;
	graph->get_vertex_label(city1, test);
	if (test != "Haval") {
		cout << "Get_vertex_label error\n";
		return 1;
	}



	string new_label = "main";
	graph->set_vertex_label(city1, new_label);
	graph->get_vertex_label(city1, test);
	if (test != "main")
	{
		cout << "Set_vertex_label error\n";
		return 1;
	}



	int test_edge_label;
	graph->get_edge_label(city1, city2, test_edge_label);
	if (test_edge_label != 100)
	{
		cout << "Get_edge_label error\n";
		return 1;
	}

	int new_edge_label = 150;
	graph->set_edge_label(city1, city2, new_edge_label);
	graph->get_edge_label(city1, city2, test_edge_label);
	if (test_edge_label != 150)
	{
		cout << "Set_edge_label error\n";
		return 1;
	}

	auto all_labels = graph->all_vertex_label();
	if (all_labels.size() != 3)
	{
		std::cout << "Get_all_vertex_labels error\n";
		return 1;
	}




	auto it = graph->get_neighbors(city1);
	int neighbor_count = 0;

	while (it.valid()) {

		neighbor_count++;
		it.next();

	}
	if (neighbor_count != 1)
	{
		cout << "Neighbor_iterator error\n";
		return 1;
	}





	graph->remove_edge(city1, city2);
	if (graph->edge_exists(city1, city2))
	{
		cout << "Remove_edge error\n";
		return 1;
	}

	graph->remove_vertex(city3);
	if (graph->vertex_count() != 2)
	{
		cout << "Remove_vertex error\n";
		return 1;
	}




	MyGraph copy(*graph);

	cout << "Vershini graph: ";
	for (size_t i = 0; i < graph->vertex_count(); i++) {
		cout << graph->vertex_name(i) << " ";
	}

	delete graph;
}