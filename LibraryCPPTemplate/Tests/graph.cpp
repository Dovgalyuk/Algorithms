#include "graph.h"
#include <iostream>

int main() {
    int vertexAmount = 5;
    auto* graph = new Graph<int,int>(vertexAmount, 1);
    for (int j = 0; j < vertexAmount; j++) {
        graph->setVertexData(j, j);
    }
    for (size_t j = 0; j < vertexAmount; j++) {
        if (graph->getData(j) != j) {
            std::cout<< "Error, wrong data" << graph->getData(j)  ;
            return 1;
        } 
    }
    graph->addEdge(0, 1);
    graph->addEdge(1,2);
    auto graphIt = graph->getIterator(0);
    while((*graphIt) != nullptr) {
        if ((*graphIt)->data != 1) {
            std::cout << "Error: iterator";
            return 1;
        }
        graphIt++;
    }
    if (!graph->containsEdge(1, 2)) {
        std::cout << "Error: containsEdge";
        return 1;
    }
    graph->setVertexData(0, 20);
    if (graph->getData(0) != 20) {
        std::cout << "Error: setVertexData";
        return 1;
    }
    graph->removeEdge(0, 1);
    if (graph->containsEdge(0, 1)) {
        std::cout << "Error: containsEdge after remove";
        return 1;
    }
    if (graph->getVertexAmount() != 5) {
        std::cout << "Error:  VertexAmount";
        return 1;
    }
    graph->removeVertex(2);
    if (graph->getVertexAmount() != 4) {
        std::cout << "Error:  VertexAmount after remove";
        return 1;
    }
    delete graph;


}