#include <iostream>	
#include "list.h"
#include "graph.h"

using namespace std;


int main() {
	int size = 10;

	Graph<int, int>* graph = new Graph<int, int>(0, size);

	//Checking the initialization
	for (int i = 0; i < 10; i++) {
		if (graph->get_vertex(i)->get_data() != 0) {
			cout << "Error initialization graph\n\n";
			return 1;
		}
	}

	//Check the correct graph size
	if (graph->size() != 10) {
		cout << "Error size graph\n";
		return 1;
	}

	//check for setting the vertex data
	for (int i = 0; i < size; i++) {
		graph->set_data_from_vertex(i, i);
	}

	for (int i = 0; i < size; i++) {
		if (graph->get_vertex_data(i) != i) {
			cout << "Error set data from vertex\n";
			return 1;
		};
	}

	//Add an edge for first vertex
	graph->get_vertex(0)->add_edge(graph->get_vertex(1), 10);

	//check for an empty edge
	if (graph->check_edge_with_empty(graph->get_vertex(0), graph->get_vertex(1)), graph->get_vertex(0)->edges[0]->get_weight() != 10) {
		cout << "Adding a edge does not work correctly.\n";
		return 1;
	}

	graph->get_vertex(0)->add_edge(graph->get_vertex(9), 25);
	graph->get_vertex(0)->add_edge(graph->get_vertex(8), 22);
	graph->get_vertex(0)->add_edge(graph->get_vertex(7), 46);
	graph->get_vertex(0)->add_edge(graph->get_vertex(6), 46);
	graph->get_vertex(0)->add_edge(graph->get_vertex(5), 46);

	//check for the setting weight
	graph->get_vertex(0)->edges[0]->set_weight(95);

	if (graph->get_vertex(0)->edges[0]->get_weight() != 95) {
		cout << "Error setting the weight or getting the weight\n";
		return -1;
	}

	//checking for deleting the weight
	graph->get_vertex(0)->remove_edge(graph->get_vertex(9));

	if (!graph->check_edge_with_empty(graph->get_vertex(0), graph->get_vertex(9))) {
		cout << "Vertex deleting error\n";
	}

	//checking for a correct iterator
	Graph<int, int>::Iterator iter(graph->get_vertex(0));

	int counter = 0;

	while (*iter != nullptr) {
		++iter;
		counter++;
	}

	if (counter != 5) {
		cout << "Iterator Error\n";
		return 1;
	}

	//checking correct edge removal
	graph->get_vertex(0)->remove_edge(graph->get_vertex(8));


	if (graph->get_vertex(0)->edges.getSize() != 4) {
		cout << "Error for deleting edge\n";
		return -1;
	}

	//checking correct vertex removal
	graph->delete_vertex(7);

	if (graph->size() != size - 1) {
		cout << "Error deleting vertex\n";
		return -1;
	}

	//checking the correct vertex index
	if (graph->find_index(graph->get_vertex(0)) != 0) {
		cout << "Error the correct vertex index\n";
	}

	//checking the correct vertex index
	if (graph->find_index_edges(0, graph->get_vertex(1)) != 0) {
		cout << "Error the correct vertex index\n";
	}

	delete graph;

	return 0;
}