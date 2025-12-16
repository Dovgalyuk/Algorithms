#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>

#include "graph.h"

using GraphType = Graph<std::string, int>;

int main()
{
    GraphType graph1(2);
    graph1.setVertexLabel(0, "A");
    graph1.setVertexLabel(1, "B");

    assert(graph1.verticesCount() == 2);
    graph1.addEdge(0, 1, 5);
    assert(graph1.hasEdge(0, 1));
    assert(graph1.getEdgeLabel(0, 1) == 5);

    graph1.setEdgeLabel(0, 1, 7);
    assert(graph1.getEdgeLabel(0, 1) == 7);

    graph1.removeEdge(0, 1);
    assert(!graph1.hasEdge(0, 1));

    GraphType graph2(1);
    graph2.setVertexLabel(0, "A");

    size_t b = graph2.addVertex("B");
    size_t c = graph2.addVertex("C");

    graph2.addEdge(0, b, 3);
    graph2.addEdge(0, c, 4);

    auto labels = graph2.getAllVertexLabels();
    assert(labels.size() == 3);
    assert(labels.get(1) == "B");

    auto it = graph2.neighbours(0);
    int totalWeight = 0;
    while (it.valid())
    {
        totalWeight += it.edgeLabel();
        it.next();
    }
    assert(totalWeight == 7);

    GraphType graph3(3);
    graph3.setVertexLabel(0, "A");
    graph3.setVertexLabel(1, "B");
    graph3.setVertexLabel(2, "C");

    graph3.addEdge(0, 1, 1);
    graph3.addEdge(1, 2, 2);
    graph3.addEdge(2, 0, 3);

    graph3.removeVertex(1);

    assert(graph3.verticesCount() == 2);
    assert(graph3.getVertexLabel(1) == "C");
    assert(graph3.hasEdge(1, 0));
    assert(!graph3.hasEdge(0, 1));
}