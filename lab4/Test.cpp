#include <iostream>
#include <vector>

#include "graph.h"

Graph* Prima(Graph* graph, Graph* prima){
    auto* Graph = graph;
    auto* Prima = prima;
    std::vector<Graph::Vertex*> vs;
    vs = Graph->GetVertices();



    return Prima;
}

int main() {
	

 auto* graph2 = new Graph();
    std::vector<Graph::Vertex*> graph2_vs;
    graph2_vs.reserve(6);

    auto* prima = new Graph();

    for(int i = 0; i < 6; ++i){
        graph2_vs.push_back(graph2->AddVertex(i));
    }
    graph2->AddEdge(*graph2_vs);

    Prima(graph2, prima);



    return 0;
}