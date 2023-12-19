#include <iostream>
#include "graph.h"

using namespace std;

typedef Graph<int> MyGraph;

int main() {

    MyGraph* graph = new MyGraph(5);

    if (graph->getVertexAmount() != 5) {
        cout << "Incorrect vertex amount\n";
        return 1;
    }

    for (size_t i = 0; i < 5; i++) {
        if (graph->getVertex(i)->getVertexData() != (int)i) {
            cout << "Incorrect vertex data\n";
            return 1;
        }
    }

    graph->addEdge(0, 3, 7);
    graph->addEdge(0, 1, 4);
    graph->addEdge(1, 4, 3);
    graph->addEdge(2, 4, 14);
    graph->addEdge(2, 5, 12);
    graph->addEdge(2, 1, 3);

    if (!graph->isEdgeExist(0, 3)) {
        cout << "Incorrect edge creation\n";
        return 1;
    }

    if (!graph->isEdgeExist(1, 4)) {
        cout << "Incorrect edge creation\n";
        return 1;
    }

    if (!graph->isEdgeExist(2, 4)) {
        cout << "Incorrect edge creation\n";
        return 1;
    }

    auto it = graph->getIterator(0);
    while (*it) {
        if (it.getIndex() != 1) {
            cout << "Invalid iteration\n";
            return 1;
        }
        ++it;
        if (it.getIndex() != 3) {
            cout << "Invalid iteration\n";
            return 1;
        }
        ++it;
    }
    
    it = graph->getIterator(1);
    
    while (*it) {
        if (it.getIndex() != 4) {
            cout << "Invalid iteration\n";
            return 1;
        }
        ++it;
    }


    if (graph->getEdge(1, 4)->getEdgeData() != 3) {
        cout << "Invalid edge data\n";
        return 1;
    }

    graph->getEdge(0, 3)->setEdgeData(30);
    if (graph->getEdge(0, 3)->getEdgeData() != 30) {
        cout << "Invalid edge data setting\n";
        return 1;
    }

    graph->removeEdge(2, 4);
    if (graph->isEdgeExist(2, 4)) {
        cout << "Invalid edge deletion\n";
        return 1;
    }

    graph->removeVertex(2);
    if (graph->getVertexAmount() != 4) {
        cout << "Invalid vertex deletion\n";
        return 1;
    }

    delete graph;
}