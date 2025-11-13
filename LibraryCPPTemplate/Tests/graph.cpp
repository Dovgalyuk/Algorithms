#include "graph.h"
#include <iostream>
using namespace std;

int main() {
    Graph<string, int> graph(3);
    graph.setVertexLabel(0, "A");
    graph.setVertexLabel(1, "B");
    graph.setVertexLabel(2, "C");

    graph.addEdge(0, 1, 5);
    graph.addEdge(1, 2, 3);

    bool allTestsPassed = true;

    if (graph.getVertexCount() != 3) allTestsPassed = false;
    if (!graph.hasEdge(0, 1)) allTestsPassed = false;
    if (graph.getEdgeLabel(0, 1) != 5) allTestsPassed = false;
    if (graph.hasEdge(1, 0)) allTestsPassed = false;
    if (graph.getVertexLabel(0) != "A") allTestsPassed = false;

    auto it = graph.getIterator(0);
    int neighborCount = 0;
    while (it.hasNext()) {
        it.next();
        neighborCount++;
    }
    if (neighborCount != 1) allTestsPassed = false;

    if (allTestsPassed) {
        cout << "All graph tests passed!" << endl;
    }
    else {
        cout << "Some tests failed!" << endl;
    }

    return 0;
}