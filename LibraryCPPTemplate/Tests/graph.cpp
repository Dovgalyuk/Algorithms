#include "graph.h"

#ifdef TEST_GRAPH_STANDALONE
#include <cassert>

int main() {
    std::cout << "=== Testing Graph Library ===" << std::endl;

    Graph<std::string, int> graph;

    size_t x = graph.addVertex("X");
    size_t y = graph.addVertex("Y");
    size_t z = graph.addVertex("Z");

    std::cout << "Added vertices: X=" << x << ", Y=" << y << ", Z=" << z << std::endl;

    std::cout << "Adding edge X->Y with weight 10... ";
    bool edge1 = graph.addEdge(x, y, 10);
    std::cout << (edge1 ? "success" : "failed") << std::endl;
    assert(edge1);

    std::cout << "Adding edge Y->Z with weight 20... ";
    bool edge2 = graph.addEdge(y, z, 20);
    std::cout << (edge2 ? "success" : "failed") << std::endl;
    assert(edge2);

    std::cout << "Adding edge X->Z with weight 5... ";
    bool edge3 = graph.addEdge(x, z, 5);
    std::cout << (edge3 ? "success" : "failed") << std::endl;
    assert(edge3);

    std::cout << "Vertex count: " << graph.getVertexCount() << std::endl;
    assert(graph.getVertexCount() == 3);

    std::cout << "Has edge X->Y: " << (graph.hasEdge(x, y) ? "true" : "false") << std::endl;
    assert(graph.hasEdge(x, y) == true);
    assert(graph.hasEdge(x, z) == true);
    assert(graph.hasEdge(y, z) == true);
    assert(graph.hasEdge(z, x) == false);

    std::cout << "Edge weight X->Y: " << graph.getEdgeLabel(x, y) << std::endl;
    assert(graph.getEdgeLabel(x, y) == 10);
    assert(graph.getEdgeLabel(x, z) == 5);
    assert(graph.getEdgeLabel(y, z) == 20);

    std::cout << "Neighbors of X: ";
    auto neighbors = graph.getNeighbors(x);
    size_t neighborCount = 0;
    while (neighbors.hasNext()) {
        size_t neighbor = neighbors.next();
        std::cout << graph.getVertexLabel(neighbor) << " ";
        neighborCount++;
    }
    std::cout << std::endl;
    assert(neighborCount == 2);

    std::cout << "\n=== Test 1: Shortest paths from X to Z ===" << std::endl;
    auto paths = graph.findAllShortestPaths(x, z);
    std::cout << "Found " << paths.size() << " shortest path(s) from X to Z" << std::endl;

    if (paths.size() > 0) {
        std::cout << "Path: ";
        for (size_t j = 0; j < paths[0].size(); ++j) {
            std::cout << graph.getVertexLabel(paths[0][j]);
            if (j < paths[0].size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << " (Length: " << paths[0].size() - 1 << ")" << std::endl;
    }

    assert(paths.size() == 1);
    assert(paths[0].size() == 2);
    assert(paths[0][0] == x);
    assert(paths[0][1] == z);

    std::cout << "\n=== Test 2: Multiple shortest paths of equal length ===" << std::endl;
    Graph<std::string, int> graph2;

    size_t A = graph2.addVertex("A");
    size_t B = graph2.addVertex("B");
    size_t C = graph2.addVertex("C");
    size_t D = graph2.addVertex("D");

    std::cout << "Added vertices: A=" << A << ", B=" << B << ", C=" << C << ", D=" << D << std::endl;

    std::cout << "Adding edge A->B... ";
    bool ab = graph2.addEdge(A, B, 1);
    std::cout << (ab ? "success" : "failed") << std::endl;
    assert(ab);

    std::cout << "Adding edge A->C... ";
    bool ac = graph2.addEdge(A, C, 1);
    std::cout << (ac ? "success" : "failed") << std::endl;
    assert(ac);

    std::cout << "Adding edge B->D... ";
    bool bd = graph2.addEdge(B, D, 1);
    std::cout << (bd ? "success" : "failed") << std::endl;
    assert(bd);

    std::cout << "Adding edge C->D... ";
    bool cd = graph2.addEdge(C, D, 1);
    std::cout << (cd ? "success" : "failed") << std::endl;
    assert(cd);

    std::cout << "\nVerifying edges:" << std::endl;
    std::cout << "  A->B: " << (graph2.hasEdge(A, B) ? "exists" : "MISSING!") << std::endl;
    std::cout << "  A->C: " << (graph2.hasEdge(A, C) ? "exists" : "MISSING!") << std::endl;
    std::cout << "  B->D: " << (graph2.hasEdge(B, D) ? "exists" : "MISSING!") << std::endl;
    std::cout << "  C->D: " << (graph2.hasEdge(C, D) ? "exists" : "MISSING!") << std::endl;

    std::cout << "\nVerifying neighbors:" << std::endl;
    std::cout << "  Neighbors of A: ";
    auto neighborsA = graph2.getNeighbors(A);
    while (neighborsA.hasNext()) {
        size_t n = neighborsA.next();
        std::cout << n << "(" << graph2.getVertexLabel(n) << ") ";
    }
    std::cout << std::endl;

    std::cout << "  Neighbors of B: ";
    auto neighborsB = graph2.getNeighbors(B);
    while (neighborsB.hasNext()) {
        size_t n = neighborsB.next();
        std::cout << n << "(" << graph2.getVertexLabel(n) << ") ";
    }
    std::cout << std::endl;

    auto paths2 = graph2.findAllShortestPaths(A, D);
    std::cout << "\nFound " << paths2.size() << " shortest path(s) from A to D" << std::endl;

    if (paths2.size() > 0) {
        for (size_t i = 0; i < paths2.size(); ++i) {
            std::cout << "Path " << i + 1 << ": ";
            for (size_t j = 0; j < paths2[i].size(); ++j) {
                std::cout << graph2.getVertexLabel(paths2[i][j]);
                if (j < paths2[i].size() - 1) {
                    std::cout << " -> ";
                }
            }
            std::cout << " (Length: " << paths2[i].size() - 1 << ")" << std::endl;
        }
    }

    assert(paths2.size() == 2);
    assert(paths2[0].size() == 3);
    assert(paths2[1].size() == 3);

    std::cout << "\n=== Test 3: Vertex removal ===" << std::endl;
    Graph<std::string, int> graph3;

    size_t v0 = graph3.addVertex("0");
    size_t v1 = graph3.addVertex("1");
    size_t v2 = graph3.addVertex("2");
    size_t v3 = graph3.addVertex("3");

    graph3.addEdge(v0, v1);
    graph3.addEdge(v1, v2);
    graph3.addEdge(v0, v2);
    graph3.addEdge(v2, v3);

    std::cout << "Before removal - Vertex count: " << graph3.getVertexCount() << std::endl;
    assert(graph3.getVertexCount() == 4);
    assert(graph3.hasEdge(v0, v1) == true);
    assert(graph3.hasEdge(v1, v2) == true);

    assert(graph3.removeVertex(v1) == true);

    std::cout << "After removal - Vertex count: " << graph3.getVertexCount() << std::endl;
    assert(graph3.getVertexCount() == 3);

    assert(graph3.hasEdge(0, 1) == true);

    auto paths3 = graph3.findAllShortestPaths(0, 2);
    std::cout << "Found " << paths3.size() << " path(s) from 0 to 2 after removal" << std::endl;
    assert(!paths3.empty());

    std::cout << "\n=== Test 4: No path exists ===" << std::endl;
    Graph<std::string, int> graph4;

    size_t g4_a = graph4.addVertex("A");
    graph4.addVertex("B");
    size_t g4_c = graph4.addVertex("C");

    graph4.addEdge(g4_a, 1);

    auto paths4 = graph4.findAllShortestPaths(g4_a, g4_c);
    std::cout << "Paths from A to C in disconnected graph: " << paths4.size() << std::endl;
    assert(paths4.empty());

    std::cout << "\n=== Test 5: Path to itself ===" << std::endl;
    auto paths5 = graph4.findAllShortestPaths(g4_a, g4_a);
    std::cout << "Paths from A to A: " << paths5.size() << std::endl;
    assert(paths5.size() == 1);
    assert(paths5[0].size() == 1);
    assert(paths5[0][0] == g4_a);

    std::cout << "\n=== All tests passed successfully! ===" << std::endl;
    return 0;
}
#endif