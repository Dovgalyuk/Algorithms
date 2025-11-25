#include <iostream>
#include <memory>
#include <random>
#include "IGraph.h"
#include "VectorGraph.h"

void testBasicOperations() {
    const std::shared_ptr<IGraph<std::string, int>> graph = std::make_shared<VectorGraph<std::string, int>>(3);

    graph->setVertex(0, "A");
    graph->setVertex(1, "B");
    graph->setVertex(2, "C");

    if(graph->getVertex(0) != "A") std::exit(1);
    if(graph->getVertex(1) != "B") std::exit(1);
    if(graph->getVertex(2) != "C") std::exit(1);

    graph->addEdge(0, 1, 5);
    graph->addEdge(1, 2, 3);
    graph->addEdge(0, 2, 7);

    if(graph->hasEdge(0, 1) != true) std::exit(1);
    if(graph->hasEdge(1, 2) != true) std::exit(1);
    if(graph->hasEdge(0, 2) != true) std::exit(1);
    if(graph->hasEdge(1, 0) != false) std::exit(1);

    if(graph->getEdge(0, 1) != 5) std::exit(1);
    if(graph->getEdge(1, 2) != 3) std::exit(1);
    if(graph->getEdge(0, 2) != 7) std::exit(1);
}

void testVertexManagement() {
    const auto graph = std::make_shared<VectorGraph<std::string, int>>(2);

    const std::size_t newIdx = graph->addVertex("NewVertex");
    if(newIdx != 2) std::exit(1);
    if(graph->vertexCount() != 3) std::exit(1);
    if(graph->getVertex(2) != "NewVertex") std::exit(1);

    graph->setVertex(1, "UpdatedVertex");
    if(graph->getVertex(1) != "UpdatedVertex") std::exit(1);

    auto& allVertices = graph->getAllVertex();
    if(allVertices.size() != 3) std::exit(1);
    if(allVertices[0] != "") std::exit(1);
    if(allVertices[1] != "UpdatedVertex") std::exit(1);
    if(allVertices[2] != "NewVertex") std::exit(1);
}

void testEdgeOperations() {
    const auto graph = std::make_shared<VectorGraph<int, double>>(3);

    graph->addEdge(0, 1, 1.5);
    graph->addEdge(1, 2, 2.5);
    graph->addEdge(2, 0, 3.5);

    if(graph->getEdge(0, 1) != 1.5) std::exit(1);
    if(graph->getEdge(1, 2) != 2.5) std::exit(1);
    if(graph->getEdge(2, 0) != 3.5) std::exit(1);

    graph->setEdge(0, 1, 4.5);
    if(graph->getEdge(0, 1) != 4.5) std::exit(1);

    graph->deleteEdge(1, 2);
    if(graph->hasEdge(1, 2) != false) std::exit(1);

    if(graph->hasEdge(0, 1) != true) std::exit(1);
    if(graph->hasEdge(2, 0) != true) std::exit(1);
}

void testNeighborIteration() {
    const auto graph = std::make_shared<VectorGraph<std::string, int>>(4);

    graph->setVertex(0, "A");
    graph->setVertex(1, "B");
    graph->setVertex(2, "C");
    graph->setVertex(3, "D");

    graph->addEdge(0, 1, 1);
    graph->addEdge(0, 2, 2);
    graph->addEdge(0, 3, 3);

    std::cout << "Neighbors of vertex 0:" << std::endl;
    Vector<std::size_t> neighborIndices;
    Vector<std::string> neighborNames;
    Vector<int> neighborWeights;

    for (auto it = graph->begin(0); it != graph->end(0); ++it) {
        auto [idx, vertex, edge] = *it;
        neighborIndices.push_back(idx);
        neighborNames.push_back(vertex);
        neighborWeights.push_back(edge);
        std::cout << idx << " (" << vertex << ") weight: " << edge << std::endl;
    }

    if(neighborIndices.size() != 3) std::exit(1);
    if(neighborWeights[0] != 1) std::exit(1);
    if(neighborWeights[1] != 2) std::exit(1);
    if(neighborWeights[2] != 3) std::exit(1);

    std::cout << "Neighbors of vertex 1 (should be empty):" << std::endl;
    int emptyNeighborCount = 0;
    for (auto it = graph->begin(1); it != graph->end(1); ++it) {
        emptyNeighborCount++;
    }
    if(emptyNeighborCount != 0) std::exit(1);
}

void testGraphClone() {
    const auto original = std::make_shared<VectorGraph<int, double>>(3);

    original->setVertex(0, 100);
    original->setVertex(1, 200);
    original->setVertex(2, 300);
    original->addEdge(0, 1, 1.5);
    original->addEdge(1, 2, 2.5);

    const auto cloned = original->clone();

    if(cloned->vertexCount() != 3) std::exit(1);
    if(cloned->getVertex(0) != 100) std::exit(1);
    if(cloned->getVertex(1) != 200) std::exit(1);
    if(cloned->getVertex(2) != 300) std::exit(1);
    if(cloned->hasEdge(0, 1) != true) std::exit(1);
    if(cloned->hasEdge(1, 2) != true) std::exit(1);
    if(cloned->getEdge(0, 1) != 1.5) std::exit(1);
    if(cloned->getEdge(1, 2) != 2.5) std::exit(1);

    original->setVertex(0, 999);
    original->deleteEdge(1, 2);

    if(cloned->getVertex(0) != 100) std::exit(1);
    if(cloned->hasEdge(1, 2) != true) std::exit(1);
}

void testErrorHandling() {
    const auto graph = std::make_shared<VectorGraph<std::string, int>>(2);

    try {
        graph->getVertex(5);
        std::exit(1);
    } catch (const std::exception& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }

    try {
        graph->addEdge(0, 5, 1);
        std::exit(1);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught expected out_of_range: " << e.what() << std::endl;
    }

    try {
        graph->getEdge(1, 0);
        std::exit(1);
    } catch (const std::logic_error& e) {
        std::cout << "Caught expected logic_error: " << e.what() << std::endl;
    }
}

void testPerformance() {
    constexpr int largeSize = 100;
    const auto largeGraph = std::make_shared<VectorGraph<int, int>>(largeSize);

    for (int i = 0; i < largeSize; ++i) {
        largeGraph->setVertex(i, i * 10);
    }

    for (int i = 0; i < largeSize; ++i) {
        for (int j = 0; j < largeSize; ++j) {
            if (i != j) {
                largeGraph->addEdge(i, j, i + j);
            }
        }
    }

    if(largeGraph->vertexCount() != largeSize) std::exit(1);
}

void testDirectedGraphProperties() {
    const auto graph = std::make_shared<VectorGraph<std::string, int>>(3);

    graph->setVertex(0, "A");
    graph->setVertex(1, "B");
    graph->setVertex(2, "C");

    graph->addEdge(0, 1, 1);
    graph->addEdge(1, 0, 2);

    if(graph->hasEdge(0, 1) != true) std::exit(1);
    if(graph->hasEdge(1, 0) != true) std::exit(1);
    if(graph->getEdge(0, 1) != 1) std::exit(1);
    if(graph->getEdge(1, 0) != 2) std::exit(1);

    graph->deleteEdge(0, 1);
    if(graph->hasEdge(0, 1) != false) std::exit(1);
    if(graph->hasEdge(1, 0) != true) std::exit(1);
}

int main() {
    testBasicOperations();
    testVertexManagement();
    testEdgeOperations();
    testNeighborIteration();
    testGraphClone();
    testErrorHandling();
    testDirectedGraphProperties();
    testPerformance();

    return 0;
}