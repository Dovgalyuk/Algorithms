#include <iostream>
#include "graph.h"

using namespace std;

typedef Graph<int> MyGraph;

int main() {
    MyGraph* graph = new MyGraph(6);

    if (graph->getVertexAmount() != 6) {
        cout << "Invalid  vertex amount\n";
        return 1;
    }


    for (size_t i = 0; i < 6; i++) {
        if (graph->getVertex(i).getVertexData() != (int)i) {
            cout << "Invalid vertex data\n";
            return 1;
        }
    }

    graph->addEdge(0, 3, 15);
    graph->addEdge(2, 1, 3);
    graph->addEdge(3, 4, 5);

    if (!graph->isEdgeExist(2, 1)) {
        std::cout << "Invalid edge creation\n";
        return 1;
    }

    auto it = graph->getIterator(0);

    if (!graph) {
        cout << "Graph does not exist\n";
        return 1;
    }

    while (*it) {
        if (it.getIndex() != 3) {
            cout << "Invalid iteration\n";
            delete graph;
            return 1;
        }
        ++it;
    }

    if (graph->getEdge(2, 1)->getEdgeData() != 3) {
        std::cout << "Invalid edge data\n";
        return 1;
    }

    graph->getEdge(0, 3)->setEdgeData(30);
    if (graph->getEdge(0, 3)->getEdgeData() != 30) {
        std::cout << "Invalid edge data setting\n";
        return 1;
    }

    graph->removeEdge(2, 1);
    if (graph->isEdgeExist(2, 1)) {
        std::cout << "Invalid edge deletion\n";
        return 1;
    }

    graph->removeVertex(3);
    if (graph->getVertexAmount() != 5) {
        std::cout << "Invalid vertex deletion\n";
        return 1;
    }

    return 0;
}