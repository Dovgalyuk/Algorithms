#include <iostream>
#include "directed_graph.h"

DirectedGraph<int, int>* readGraph() {
    int vertexAmount , edgeAmount;
    std::cin >> vertexAmount >> edgeAmount;
    auto* graph = new DirectedGraph<int, int>(vertexAmount, 1);
    for (int i = 0; i < vertexAmount; ++i) {
        graph->getVertex(i)->data = i;
    }
    for (int i = 0; i < edgeAmount; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph->addEdge(graph->getVertex(from), graph->getVertex(to), i);
    }
    return graph;
}

bool* createWasArray(int size) {
    bool* was = new bool[size];
    for (int i = 0; i < size; ++i) {
        was[i] = false;
    }
    return was;
}



int main() {
    DirectedGraph<int, int>* graph = readGraph();



    delete graph;
}
