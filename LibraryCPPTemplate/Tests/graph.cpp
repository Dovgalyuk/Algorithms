#include "graph.h"
#include "vector.h"
#include <iostream>
#include <cassert>

int main() {
    Graph<std::string, double> g(3);
    g.setVertexLabel(0, "A");
    g.setVertexLabel(1, "B");
    g.setVertexLabel(2, "C");

    g.addEdge(0, 1, 1.0);
    g.addEdge(1, 2, 2.0);
    assert(g.hasEdge(0, 1));
    assert(!g.hasEdge(1, 0));
    assert(g.getEdgeLabel(0, 1).value() == 1.0);

    assert(g.getVertexLabel(0) == "A");
    auto labels = g.getAllVertexLabels();
    assert(labels.size() == 3 && labels[0] == "A");

    g.addVertex("D");
    assert(g.numVertices() == 4);
    assert(g.getVertexLabel(3) == "D");

    g.removeEdge(0, 1);
    assert(!g.hasEdge(0, 1));

    g.addEdge(0, 2, 3.0);
    auto it = g.beginNeighbors(0);
    assert(*it == 2);
    ++it;
    assert(it == g.endNeighbors(0));

    g.removeVertex(1);
    assert(g.numVertices() == 3);
    assert(g.getVertexLabel(0) == "A");
    assert(g.getVertexLabel(1) == "C");
    assert(g.getVertexLabel(2) == "D");

    std::cout << "All graph tests passed!" << std::endl;
    return 0;
}