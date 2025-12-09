#include "graph.h"

#ifdef TEST_GRAPH_STANDALONE
#include <cassert>

int main() {
    std::cout << "=== Testing Graph Library ===" << std::endl;

    Graph<std::string, int> graph(3);

    assert(graph.setVertexLabel(0, "X"));
    assert(graph.setVertexLabel(1, "Y"));
    assert(graph.setVertexLabel(2, "Z"));

    assert(graph.getVertexLabel(0) == "X");
    assert(graph.getVertexLabel(1) == "Y");
    assert(graph.getVertexLabel(2) == "Z");

    assert(graph.addEdge(0, 1, 10));
    assert(graph.addEdge(1, 2, 20));
    assert(graph.addEdge(0, 2, 5));

    std::cout << "Vertex count: " << graph.getVertexCount() << std::endl;
    assert(graph.getVertexCount() == 3);

    std::cout << "Has edge X->Y: " << graph.hasEdge(0, 1) << std::endl;
    assert(graph.hasEdge(0, 1) == true);
    assert(graph.hasEdge(0, 2) == true);
    assert(graph.hasEdge(1, 2) == true);
    assert(graph.hasEdge(2, 0) == false);

    std::cout << "Edge weight X->Y: " << graph.getEdgeLabel(0, 1) << std::endl;
    assert(graph.getEdgeLabel(0, 1) == 10);
    assert(graph.getEdgeLabel(0, 2) == 5);
    assert(graph.getEdgeLabel(1, 2) == 20);

    std::cout << "Neighbors of X: ";
    auto neighbors = graph.getNeighbors(0);
    size_t neighborCount = 0;
    while (neighbors.hasNext()) {
        size_t neighbor = neighbors.next();
        std::cout << graph.getVertexLabel(neighbor) << " ";
        neighborCount++;
    }
    std::cout << std::endl;
    assert(neighborCount == 2);

    std::cout << "\n=== Test 1: Shortest paths from X to Z ===" << std::endl;
    auto paths = graph.findAllShortestPaths(0, 2);
    std::cout << "Found " << paths.size() << " shortest path(s) from X to Z" << std::endl;

    assert(paths.size() == 1);

    assert(paths[0].size() == 2);
    assert(paths[0][0] == 0);
    assert(paths[0][1] == 2);

    std::cout << "Path: ";
    for (size_t j = 0; j < paths[0].size(); ++j) {
        std::cout << graph.getVertexLabel(paths[0][j]);
        if (j < paths[0].size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << " (Length: " << paths[0].size() - 1 << ")" << std::endl;

    std::cout << "\n=== Test 2: Multiple shortest paths of equal length ===" << std::endl;
    Graph<std::string, int> graph2;

    size_t A = graph2.addVertex("A");
    size_t B = graph2.addVertex("B");
    size_t C = graph2.addVertex("C");
    size_t D = graph2.addVertex("D");

    assert(graph2.addEdge(A, B, 1));
    assert(graph2.addEdge(A, C, 1));
    assert(graph2.addEdge(B, D, 1));
    assert(graph2.addEdge(C, D, 1));

    auto paths2 = graph2.findAllShortestPaths(A, D);
    std::cout << "Found " << paths2.size() << " shortest path(s) from A to D" << std::endl;

    assert(paths2.size() == 2);
    assert(paths2[0].size() == 3);
    assert(paths2[1].size() == 3);

    assert(paths2[0][0] == A);
    assert(paths2[0][1] == B || paths2[0][1] == C);
    assert(paths2[0][2] == D);

    assert(paths2[1][0] == A);
    assert(paths2[1][1] != paths2[0][1]);
    assert(paths2[1][2] == D);

    for (size_t i = 0; i < paths2.size(); ++i) {
        std::cout << "Path " << i + 1 << ": ";
        for (size_t j = 0; j < paths2[i].size(); ++j) {
            std::cout << graph2.getVertexLabel(paths2[i][j]);
            if (j < paths2[i].size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }

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
    assert(graph3.hasEdge(1, 2) == true);

    auto paths3 = graph3.findAllShortestPaths(0, 2);
    std::cout << "Found " << paths3.size() << " path(s) from 0 to 2 after removal" << std::endl;
    assert(!paths3.empty());

    std::cout << "\n=== Test 4: No path exists ===" << std::endl;
    Graph<std::string, int> graph4;

    size_t g4_a = graph4.addVertex("A");
    size_t g4_b = graph4.addVertex("B");
    size_t g4_c = graph4.addVertex("C");

    graph4.addEdge(g4_a, g4_b);

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