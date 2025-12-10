#include <iostream>
#include "IGraph.h"
#include "AdjacencyMatrixGraph.h"
#include "BFSShortestPaths.h"

void testGraphLibrary() {
    std::cout << "Testing Graph Library with Adjacency Matrix\n";

    AdjacencyMatrixGraph<std::string, double> graph;
    graph.initialize(5);

    graph.setVertex(0, "A");
    graph.setVertex(1, "B");
    graph.setVertex(2, "C");
    graph.setVertex(3, "D");
    graph.setVertex(4, "E");

    graph.addEdge(0, 1, 2.0);
    graph.addEdge(0, 2, 4.0);
    graph.addEdge(1, 2, 1.0);
    graph.addEdge(1, 3, 7.0);
    graph.addEdge(2, 3, 3.0);
    graph.addEdge(3, 4, 1.0);
    graph.addEdge(2, 4, 5.0);

    std::cout << "Vertex count: " << graph.vertexCount() << "\n";
    std::cout << "Has edge A->B: " << graph.hasEdge(0, 1) << "\n";
    std::cout << "Edge weight A->B: " << graph.getEdge(0, 1) << "\n";

    std::cout << "\nNeighbors of B:\n";
    auto neighborIter = graph.createNeighborIterator(1);
    while (neighborIter->hasNext()) {
        auto [idx, name, weight] = neighborIter->next();
        std::cout << "  -> " << name << " (weight: " << weight << ")\n";
    }

    std::cout << "\nFinding all shortest paths from A to E:\n";
    auto paths = BFSShortestPaths<std::string, double>::findAllShortestPaths(graph, "A", "E");

    for (const auto& pathInfo : paths) {
        std::cout << "Path (cost: " << pathInfo.totalCost << "): ";
        for (std::size_t vertex : pathInfo.vertices) {
            std::cout << graph.getVertex(vertex) << " ";
        }
        std::cout << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--test") {
        testGraphLibrary();
        return 0;
    }

    testGraphLibrary();
    return 0;
}