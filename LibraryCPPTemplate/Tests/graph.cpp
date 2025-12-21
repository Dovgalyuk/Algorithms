#include <iostream>
#include <string>
#include "vectorT.h"
#include "graph.h"

int main() {
    std::cout << "Testing Digraph implementation...\n";

    Digraph<std::string, int> graph(5);
    if (graph.countVertices() != 5) {
        std::cerr << "FAIL: Initial vertex count incorrect\n";
        return 1;
    }
    std::cout << "PASS: Graph created with 5 vertices\n";

    graph.setVertexLabel(0, "A");
    graph.setVertexLabel(1, "B");
    graph.setVertexLabel(2, "C");
    graph.setVertexLabel(3, "D");
    graph.setVertexLabel(4, "E");

    if (graph.getVertexLabel(0) != "A" || graph.getVertexLabel(4) != "E") {
        std::cerr << "FAIL: Vertex labels not set correctly\n";
        return 1;
    }
    std::cout << "PASS: Vertex labels set correctly\n";

    if (!graph.addEdge(0, 1, 10) ||
        !graph.addEdge(0, 2, 5) ||
        !graph.addEdge(1, 3, 7) ||
        !graph.addEdge(2, 3, 3) ||
        !graph.addEdge(3, 4, 2)) {
        std::cerr << "FAIL: Failed to add edges\n";
        return 1;
    }
    std::cout << "PASS: Edges added successfully\n";

    if (!graph.hasEdge(0, 1) || graph.hasEdge(1, 0)) {
        std::cerr << "FAIL: Edge existence check failed\n";
        return 1;
    }
    std::cout << "PASS: Edge existence check passed\n";

    if (graph.getEdgeLabel(0, 1) != 10 || graph.getEdgeLabel(2, 3) != 3) {
        std::cerr << "FAIL: Edge labels incorrect\n";
        return 1;
    }
    std::cout << "PASS: Edge labels retrieved correctly\n";

    std::cout << "Testing neighbor iterator for vertex 0:\n";
    int neighborCount = 0;
    bool neighbor1Found = false;
    bool neighbor2Found = false;
    
    for (auto it = graph.neighborBegin(0); it != graph.neighborEnd(0); ++it) {
        auto [neighbor, weight] = *it;
        std::cout << "  Neighbor " << neighbor << " (weight: " << weight << ")\n";
        
        if (neighbor == 1 && weight == 10) {
            neighbor1Found = true;
        }
        if (neighbor == 2 && weight == 5) {
            neighbor2Found = true;
        }
        
        ++neighborCount;
    }

    if (neighborCount != 2) {
        std::cerr << "FAIL: Iterator found wrong number of neighbors\n";
        return 1;
    }
    
    if (!neighbor1Found || !neighbor2Found) {
        std::cerr << "FAIL: Neighbor iterator did not find expected neighbors\n";
        return 1;
    }
    std::cout << "PASS: Neighbor iterator works correctly with correct neighbors\n";

    if (!graph.setEdgeLabel(0, 1, 15) || graph.getEdgeLabel(0, 1) != 15) {
        std::cerr << "FAIL: Failed to update edge label\n";
        return 1;
    }
    std::cout << "PASS: Edge label updated successfully\n";

    if (!graph.removeEdge(0, 2) || graph.hasEdge(0, 2)) {
        std::cerr << "FAIL: Failed to remove edge\n";
        return 1;
    }
    std::cout << "PASS: Edge removed successfully\n";

    size_t newVertex = graph.addVertex();
    if (newVertex != 5 || graph.countVertices() != 6) {
        std::cerr << "FAIL: Failed to add vertex\n";
        return 1;
    }
    graph.setVertexLabel(newVertex, "F");
    graph.addEdge(newVertex, 0, 8);
    std::cout << "PASS: Vertex added successfully\n";

    auto allLabels = graph.getAllVertexLabels();
    if (allLabels.size() != 6) {
        std::cerr << "FAIL: getAllVertexLabels returned wrong size\n";
        return 1;
    }
    std::cout << "PASS: getAllVertexLabels works correctly\n";

    int vertexId = graph.getVertexId("B");
    if (vertexId != 1) {
        std::cerr << "FAIL: getVertexId returned wrong ID\n";
        return 1;
    }
    std::cout << "PASS: getVertexId works correctly\n";

    if (!graph.removeVertex(2) || graph.countVertices() != 5) {
        std::cerr << "FAIL: Failed to remove vertex\n";
        return 1;
    }
    std::cout << "PASS: Vertex removed successfully\n";

    Digraph<int, int> largeGraph(1000);
    for (size_t i = 0; i < 1000; ++i) {
        for (size_t j = 0; j < 1000; ++j) {
            if (i != j && (i + j) % 3 == 0) {
                largeGraph.addEdge(i, j, i + j);
            }
        }
    }
    std::cout << "PASS: Performance test completed\n";

    std::cout << "\nFinal adjacency matrix:\n";
    graph.printAdjacencyMatrix();

    std::cout << "\nALL TESTS PASSED!\n";
    return 0;
}
