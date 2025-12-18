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

    GraphType graph4(3);
    graph4.setVertexLabel(0, "A");
    graph4.setVertexLabel(1, "B");
    graph4.setVertexLabel(2, "C");

    graph4.addEdge(0, 1, 10);
    graph4.addEdge(0, 2, 20);
    graph4.addEdge(0, 0, 30);

    graph4.removeEdge(0, 2);

    auto neighboursBeforeRemoval = graph4.neighbours(0);
    int neighbourCount = 0;
    bool hasSelfLoop = false;
    bool hasEdgeToOne = false;
    while (neighboursBeforeRemoval.valid())
    {
        const auto vertex = neighboursBeforeRemoval.vertex();
        if (vertex == 0)
        {
            hasSelfLoop = neighboursBeforeRemoval.edgeLabel() == 30;
        }
        else if (vertex == 1)
        {
            hasEdgeToOne = neighboursBeforeRemoval.edgeLabel() == 10;
        }
        ++neighbourCount;
        neighboursBeforeRemoval.next();
    }
    assert(neighbourCount == 2);
    assert(hasSelfLoop);
    assert(hasEdgeToOne);

    graph4.removeVertex(1);

    assert(graph4.verticesCount() == 2);
    assert(graph4.getVertexLabel(1) == "C");

    auto neighboursAfterRemoval = graph4.neighbours(0);
    neighbourCount = 0;
    hasSelfLoop = false;
    hasEdgeToOne = false;
    while (neighboursAfterRemoval.valid())
    {
        const auto vertex = neighboursAfterRemoval.vertex();
        if (vertex == 0)
        {
            hasSelfLoop = neighboursAfterRemoval.edgeLabel() == 30;
        }
        else if (vertex == 1)
        {
            hasEdgeToOne = true;
        }
        ++neighbourCount;
        neighboursAfterRemoval.next();
    }

    assert(neighbourCount == 1);
    assert(hasSelfLoop);
    assert(!hasEdgeToOne);
}
