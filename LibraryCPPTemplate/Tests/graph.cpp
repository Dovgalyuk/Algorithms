#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

#include "graph.h"

using graph::Graph;

static void testAddVerticesEdges() {
    Graph<std::string, int> g(3);
    g.vertexLabel(0) = "A";
    g.vertexLabel(1) = "B";
    g.vertexLabel(2) = "C";
    assert(g.vertexCount() == 3);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 20);
    g.addEdge(0, 2, 30);
    assert(g.hasEdge(0, 1));
    assert(g.hasEdge(1, 2));
    assert(g.hasEdge(0, 2));
    assert(!g.hasEdge(2, 0));
    g.edgeLabel(0, 1) = 11;
    assert(g.edgeLabel(0, 1) == 11);
    std::cout << "[OK] testAddVerticesEdges\n";
}

static void testRemoveEdgeVertex() {
    Graph<std::string, int> g(4);
    g.vertexLabel(0) = "A";
    g.vertexLabel(1) = "B";
    g.vertexLabel(2) = "C";
    g.vertexLabel(3) = "D";
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    g.removeEdge(1, 2);
    assert(!g.hasEdge(1, 2));
    assert(g.hasEdge(2, 3));
    g.removeVertex(1);
    assert(g.vertexCount() == 3);
    assert(g.vertexLabel(0) == "A");
    assert(g.vertexLabel(1) == "C");
    assert(g.vertexLabel(2) == "D");
    assert(g.hasEdge(1, 2));
    assert(!g.hasEdge(0, 1));
    std::cout << "[OK] testRemoveEdgeVertex\n";
}

static void testNeighborIterator() {
    Graph<std::string, int> g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 7);
    int sum = 0;
    int count = 0;
    for (auto it = g.neighbors(0).begin(); it != g.neighbors(0).end(); ++it) {
        auto p = *it;
        sum += p.second;
        ++count;
    }
    assert(count == 3);
    assert(sum == 18);
    std::cout << "[OK] testNeighborIterator\n";
}

static void testReadFromStream() {
    std::istringstream in("3\nA\nB\nC\n2\n0 1 100\n1 2 200\n");
    Graph<std::string, int> g;
    g.readFrom(in);
    assert(g.vertexCount() == 3);
    assert(g.vertexLabel(0) == "A");
    assert(g.edgeLabel(0, 1) == 100);
    assert(g.edgeLabel(1, 2) == 200);
    std::cout << "[OK] testReadFromStream\n";
}

static void testVertexLabelsVector() {
    Graph<std::string, int> g;
    g.addVertex("X");
    g.addVertex("Y");
    auto labels = g.vertexLabels();
    assert(labels.size() == 2);
    assert(labels[0] == "X");
    assert(labels[1] == "Y");
    std::cout << "[OK] testVertexLabelsVector\n";
}

int main() {
    testAddVerticesEdges();
    testRemoveEdgeVertex();
    testNeighborIterator();
    testReadFromStream();
    testVertexLabelsVector();
    std::cout << "All graph tests passed.\n";
    return 0;
}
