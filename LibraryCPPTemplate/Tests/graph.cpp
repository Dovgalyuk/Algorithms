#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "graph.h"

using graph::Graph;

static void check(bool cond, const char* expr, const char* file, int line) {
    if (!cond) {
        std::cerr << "CHECK failed: " << expr << " at " << file << ":" << line << "\n";
        std::exit(1);
    }
}

static void testAddVerticesEdges() {
    Graph<std::string, int> g(3);
    g.vertexLabel(0) = "A";
    g.vertexLabel(1) = "B";
    g.vertexLabel(2) = "C";
    check(g.vertexCount() == 3, "g.vertexCount() == 3", __FILE__, __LINE__);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 20);
    g.addEdge(0, 2, 30);
    check(g.hasEdge(0, 1), "g.hasEdge(0, 1)", __FILE__, __LINE__);
    check(g.hasEdge(1, 2), "g.hasEdge(1, 2)", __FILE__, __LINE__);
    check(g.hasEdge(0, 2), "g.hasEdge(0, 2)", __FILE__, __LINE__);
    check(!g.hasEdge(2, 0), "!g.hasEdge(2, 0)", __FILE__, __LINE__);
    g.edgeLabel(0, 1) = 11;
    check(g.edgeLabel(0, 1) == 11, "g.edgeLabel(0, 1) == 11", __FILE__, __LINE__);
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
    check(!g.hasEdge(1, 2), "!g.hasEdge(1, 2)", __FILE__, __LINE__);
    check(g.hasEdge(2, 3), "g.hasEdge(2, 3)", __FILE__, __LINE__);
    g.removeVertex(1);
    check(g.vertexCount() == 3, "g.vertexCount() == 3", __FILE__, __LINE__);
    check(g.vertexLabel(0) == "A", "g.vertexLabel(0) == A", __FILE__, __LINE__);
    check(g.vertexLabel(1) == "C", "g.vertexLabel(1) == C", __FILE__, __LINE__);
    check(g.vertexLabel(2) == "D", "g.vertexLabel(2) == D", __FILE__, __LINE__);
    check(g.hasEdge(1, 2), "g.hasEdge(1, 2)", __FILE__, __LINE__);
    check(!g.hasEdge(0, 1), "!g.hasEdge(0, 1)", __FILE__, __LINE__);
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
    check(count == 3, "count == 3", __FILE__, __LINE__);
    check(sum == 18, "sum == 18", __FILE__, __LINE__);
    std::cout << "[OK] testNeighborIterator\n";
}

static void testReadFromStream() {
    std::istringstream in("3\nA\nB\nC\n2\n0 1 100\n1 2 200\n");
    Graph<std::string, int> g;
    g.readFrom(in);
    check(g.vertexCount() == 3, "g.vertexCount() == 3", __FILE__, __LINE__);
    check(g.vertexLabel(0) == "A", "g.vertexLabel(0) == A", __FILE__, __LINE__);
    check(g.edgeLabel(0, 1) == 100, "g.edgeLabel(0, 1) == 100", __FILE__, __LINE__);
    check(g.edgeLabel(1, 2) == 200, "g.edgeLabel(1, 2) == 200", __FILE__, __LINE__);
    std::cout << "[OK] testReadFromStream\n";
}

int main() {
    testAddVerticesEdges();
    testRemoveEdgeVertex();
    testNeighborIterator();
    testReadFromStream();
    std::cout << "All graph tests passed.\n";
    return 0;
}
