#include <iostream>
#include "graph.h"
#include <vector>


int main() {
	
	Graph* graph = new Graph();
	std::vector<Vertex*> vs;

	for (int i = 0; i < 4; i++) {
		vs.push_back(graph->AddVertex(i)) ;
	}
	/*
	v0->v0
	v0->v1
	v0->v3
	v2->v3
	v2->v3 (test, duplicates are not allowed)
	*/
	graph->AddEdge(*vs.at(0), *vs.at(0));
	graph->AddEdge(*vs.at(0), *vs.at(1));
	graph->AddEdge(*vs.at(0), *vs.at(3));
	graph->AddEdge(*vs.at(2), *vs.at(3));

	if (graph->AddEdge(*vs.at(2), *vs.at(3))) {
		exit(1);
	}

	graph->GetSuccessors(*vs.at(0));
	graph->RemoveEdge(*vs.at(0), *vs.at(1));
	if (graph->GetEdge(*vs.at(0), *vs.at(1))) {
		exit(1);
	}

	graph->AddEdge(*vs.at(0), *vs.at(1));
	if (!graph->GetEdge(*vs.at(0), *vs.at(1))) {
		exit(1);
	}

	graph->GetSuccessors(*vs.at(0));


	graph->GetVertices();
	graph->RemoveVertex(*vs.at(3));
	graph->GetVertices();

}