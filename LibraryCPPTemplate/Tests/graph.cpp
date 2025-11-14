#include "graph.h"
#include <iostream>
using namespace std;

int main() {
    Graph<string, int> graph(3);
    graph.setVertexLabel(0, "A");
    graph.setVertexLabel(1, "B");
    graph.setVertexLabel(2, "C");

    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);  
    graph.addEdge(1, 2, 4);

    bool allTestsPassed = true;

    if (graph.getVertexCount() != 3) allTestsPassed = false;
    if (!graph.hasEdge(0, 1)) allTestsPassed = false;
    if (graph.getEdgeLabel(0, 1) != 5) allTestsPassed = false;
    if (graph.hasEdge(1, 0)) allTestsPassed = false;
    if (graph.getVertexLabel(0) != "A") allTestsPassed = false;

    graph.setEdgeLabel(0, 1, 10);
    if (graph.getEdgeLabel(0, 1) != 10) allTestsPassed = false;

    graph.removeEdge(0, 1);
    if (graph.hasEdge(0, 1)) allTestsPassed = false;

    size_t newVertex = graph.addVertex("D");
    if (graph.getVertexCount() != 4) allTestsPassed = false;
    if (graph.getVertexLabel(newVertex) != "D") allTestsPassed = false;

    graph.addEdge(0, newVertex, 7);
    if (!graph.hasEdge(0, newVertex)) allTestsPassed = false;
    if (graph.getEdgeLabel(0, newVertex) != 7) allTestsPassed = false;

    auto it = graph.getIterator(0);
    int neighborCount = 0;
    bool hasNeighbor2 = false, hasNeighbor3 = false;
    while (it.hasNext()) {
        size_t neighbor = it.next();
        neighborCount++;
        if (neighbor == 2) hasNeighbor2 = true;
        if (neighbor == 3) hasNeighbor3 = true;  
    }
    if (neighborCount != 2 || !hasNeighbor2 || !hasNeighbor3) {
        allTestsPassed = false;
    }

    it = graph.getIterator(1);
    neighborCount = 0;
    while (it.hasNext()) {
        it.next();
        neighborCount++;
    }
    if (neighborCount != 1) allTestsPassed = false;

    it = graph.getIterator(2);
    if (it.hasNext()) allTestsPassed = false;

    if (allTestsPassed) {
        cout << "All graph tests passed!" << endl;
        return 0;  
    }
    else {
        cout << "Some tests failed!" << endl;
        return 1;  
    }
}