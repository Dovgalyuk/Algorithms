#include <iostream>
#include <vector>

#include "graph.h"

int main() {

    auto* graph = new Graph();


    std::vector<Graph::Vertex*> vs;
    vs.reserve(4);
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
    //graph->AddEdge(*vs.at(0), *vs.at(0), 5);
    graph->AddEdge(*vs.at(0), *vs.at(1), 3);

    graph->AddEdge(*vs.at(0), *vs.at(3), 6);
    graph->AddEdge(*vs.at(2), *vs.at(3), 2);

    if (!graph->AddEdge(*vs.at(2), *vs.at(3),2)) {
        return 1;
    }

    if(!graph->IsEdge(*vs.at(0), *vs.at(1))){
        return 1;
    }

    graph->GetSuccessors(*vs.at(0));

    graph->RemoveEdge(*vs.at(0), *vs.at(1));
    if (graph->IsEdge(*vs.at(0), *vs.at(1))) {
        return 1;
    }

    graph->AddEdge(*vs.at(0), *vs.at(1), 1);
    if (!graph->IsEdge(*vs.at(0), *vs.at(1))) {
        exit(1);
    }

    std::vector<Graph::Vertex*> suc;
    suc = graph->GetSuccessors(*vs.at(0));
    std::cout << "Successors of 0: " << std::endl;
    for (auto& vert: suc) {
        std::cout << vert->GetData() << std::endl;
    }


    graph->GetVertices();
    graph->RemoveVertex(*vs.at(3));
    if (graph->IsEdge(*vs.at(2), *vs.at(3))) {
        return 1;
    }
    vs = graph->GetVertices();
    std::cout << "Vertices: "<<std::endl;
    for (auto& vert: vs) {
        std::cout << vert->GetData() << std::endl;
    }

    return 0;
}
