#include <iostream>
#include <cassert>
#include <memory>
#include <random>
#include "IGraph.h"
#include "VectorGraph.h"

void testBasicOperations() {
    const std::shared_ptr<IGraph<std::string, int>> graph = std::make_shared<VectorGraph<std::string, int>>(3);

    graph->setVertex(0, "A");
    graph->setVertex(1, "B");
    graph->setVertex(2, "C");

    assert(graph->getVertex(0) == "A");
    assert(graph->getVertex(1) == "B");
    assert(graph->getVertex(2) == "C");

    graph->addEdge(0, 1, 5);
    graph->addEdge(1, 2, 3);
    graph->addEdge(0, 2, 7);

    assert(graph->hasEdge(0, 1) == true);
    assert(graph->hasEdge(1, 2) == true);
    assert(graph->hasEdge(0, 2) == true);
    assert(graph->hasEdge(1, 0) == false);

    assert(graph->getEdge(0, 1) == 5);
    assert(graph->getEdge(1, 2) == 3);
    assert(graph->getEdge(0, 2) == 7);
}

void testVertexManagement() {
    const auto graph = std::make_shared<VectorGraph<std::string, int>>(2);

    const std::size_t newIdx = graph->addVertex("NewVertex");
    assert(newIdx == 2);
    assert(graph->vertexCount() == 3);
    assert(graph->getVertex(2) == "NewVertex");

    graph->setVertex(1, "UpdatedVertex");
    assert(graph->getVertex(1) == "UpdatedVertex");

    auto& allVertices = graph->getAllVertex();
    assert(allVertices.size() == 3);
    assert(allVertices[0] == "");
    assert(allVertices[1] == "UpdatedVertex");
    assert(allVertices[2] == "NewVertex");
}

void testEdgeOperations() {
    const auto graph = std::make_shared<VectorGraph<int, double>>(3);

    graph->addEdge(0, 1, 1.5);
    graph->addEdge(1, 2, 2.5);
    graph->addEdge(2, 0, 3.5);

    assert(graph->getEdge(0, 1) == 1.5);
    assert(graph->getEdge(1, 2) == 2.5);
    assert(graph->getEdge(2, 0) == 3.5);

    graph->setEdge(0, 1, 4.5);
    assert(graph->getEdge(0, 1) == 4.5);

    graph->deleteEdge(1, 2);
    assert(graph->hasEdge(1, 2) == false);

    assert(graph->hasEdge(0, 1) == true);
    assert(graph->hasEdge(2, 0) == true);
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

    assert(neighborIndices.size() == 3);
    assert(neighborWeights[0] == 1);
    assert(neighborWeights[1] == 2);
    assert(neighborWeights[2] == 3);

    std::cout << "Neighbors of vertex 1 (should be empty):" << std::endl;
    int emptyNeighborCount = 0;
    for (auto it = graph->begin(1); it != graph->end(1); ++it) {
        emptyNeighborCount++;
    }
    assert(emptyNeighborCount == 0);
}

void testGraphClone() {
    const auto original = std::make_shared<VectorGraph<int, double>>(3);

    original->setVertex(0, 100);
    original->setVertex(1, 200);
    original->setVertex(2, 300);
    original->addEdge(0, 1, 1.5);
    original->addEdge(1, 2, 2.5);

    const auto cloned = original->clone();

    assert(cloned->vertexCount() == 3);
    assert(cloned->getVertex(0) == 100);
    assert(cloned->getVertex(1) == 200);
    assert(cloned->getVertex(2) == 300);
    assert(cloned->hasEdge(0, 1) == true);
    assert(cloned->hasEdge(1, 2) == true);
    assert(cloned->getEdge(0, 1) == 1.5);
    assert(cloned->getEdge(1, 2) == 2.5);

    original->setVertex(0, 999);
    original->deleteEdge(1, 2);

    assert(cloned->getVertex(0) == 100);
    assert(cloned->hasEdge(1, 2) == true);
}

void testErrorHandling() {
    const auto graph = std::make_shared<VectorGraph<std::string, int>>(2);

    try {
        graph->getVertex(5);
        assert(false);
    } catch (const std::exception& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }

    try {
        graph->addEdge(0, 5, 1);
        assert(false);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught expected out_of_range: " << e.what() << std::endl;
    }

    try {
        graph->getEdge(1, 0);
        assert(false);
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

    assert(largeGraph->vertexCount() == largeSize);
}

void testDirectedGraphProperties() {
    const auto graph = std::make_shared<VectorGraph<std::string, int>>(3);

    graph->setVertex(0, "A");
    graph->setVertex(1, "B");
    graph->setVertex(2, "C");

    graph->addEdge(0, 1, 1);
    graph->addEdge(1, 0, 2);

    assert(graph->hasEdge(0, 1) == true);
    assert(graph->hasEdge(1, 0) == true);
    assert(graph->getEdge(0, 1) == 1);
    assert(graph->getEdge(1, 0) == 2);

    graph->deleteEdge(0, 1);
    assert(graph->hasEdge(0, 1) == false);
    assert(graph->hasEdge(1, 0) == true);
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