#include "graph.h"
#include <iostream>
#include <string>
#include <vector>

bool check(bool condition, const char *message)
{
    if (!condition)
    {
        std::cout << "Test failed: " << message << '\n';
        return false;
    }
    return true;
}

int main()
{
    bool ok = true;

    Graph<int, std::string> g(3);
    g.setVertexLabel(0, "A");
    g.setVertexLabel(1, "B");
    g.setVertexLabel(2, "C");

    ok &= check(g.vertexCount() == 3, "vertexCount after constructor");

    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 3);

    ok &= check(g.hasEdge(0, 1), "edge 0->1 exists");
    ok &= check(g.hasEdge(0, 2), "edge 0->2 exists");
    ok &= check(!g.hasEdge(2, 0), "edge 2->0 does not exist");

    std::vector<std::size_t> neighbors0;
    for (auto it = g.neighborsBegin(0); it != g.neighborsEnd(0); ++it)
    {
        neighbors0.push_back(*it);
    }

    ok &= check(neighbors0.size() == 2, "neighbor count for vertex 0");
    if (neighbors0.size() == 2)
    {
        ok &= check(neighbors0[0] == 1 && neighbors0[1] == 2, "neighbors of 0 are 1 and 2");
    }

    auto labels = g.getAllVertexLabels();
    ok &= check(labels.size() == 3, "labels size is 3");
    if (labels.size() == 3)
    {
        ok &= check(labels[0] == "A" && labels[1] == "B" && labels[2] == "C", "labels content");
    }

    std::size_t d = g.addVertex("D");
    ok &= check(d == 3, "index of new vertex D");
    ok &= check(g.vertexCount() == 4, "vertexCount after addVertex");
    ok &= check(g.getVertexLabel(d) == "D", "label of new vertex D");

    g.addEdge(d, 0, 7);
    ok &= check(g.hasEdge(d, 0), "edge D->0 exists");

    g.removeEdge(0, 1);
    ok &= check(!g.hasEdge(0, 1), "edge 0->1 removed");

    g.removeVertex(1);
    ok &= check(g.vertexCount() == 3, "vertexCount after removeVertex");

    std::vector<std::size_t> neighborsAfter;
    for (auto it = g.neighborsBegin(0); it != g.neighborsEnd(0); ++it)
    {
        neighborsAfter.push_back(*it);
    }

    ok &= check(neighborsAfter.size() == 1, "neighbors count after removeVertex");
    if (neighborsAfter.size() == 1)
    {
        ok &= check(neighborsAfter[0] == 1, "remaining neighbor index after removeVertex");
    }

    if (!ok)
    {
        std::cout << "Graph tests failed\n";
        return 1;
    }

    std::cout << "Graph tests passed\n";
    return 0;
}

