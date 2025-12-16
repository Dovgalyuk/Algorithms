#include <iostream>
#include "vector.h"
#include "graph.h"

typedef Digraph<std::string, int> MyGraph;
typedef Vector<int> MyVector;

void testGraphOperations() {
    std::cout << "Testing graph operations...\n";

    MyGraph graph(3);

    graph.setvertlabel(0, "A");
    graph.setvertlabel(1, "B");
    graph.setvertlabel(2, "C");

    if (!graph.addedge(0, 1, 5)) {
        std::cout << "Failed to add edge 0->1\n";
        return;
    }

    if (!graph.addedge(1, 2, 3)) {
        std::cout << "Failed to add edge 1->2\n";
        return;
    }

    if (!graph.addedge(0, 2, 10)) {
        std::cout << "Failed to add edge 0->2\n";
        return;
    }

    if (!graph.hasedge(0, 1)) {
        std::cout << "Test failed: edge 0->1 should exist\n";
        return;
    }

    if (graph.hasedge(1, 0)) {
        std::cout << "Test failed: edge 1->0 should not exist\n";
        return;
    }

    if (graph.getedgelabel(0, 1) != 5) {
        std::cout << "Test failed: edge label incorrect\n";
        return;
    }

    if (graph.countvert() != 3) {
        std::cout << "Test failed: vertex count incorrect\n";
        return;
    }

    if (graph.getvertexlabel(0) != "A") {
        std::cout << "Test failed: vertex label incorrect\n";
        return;
    }

    std::cout << "Neighbors of A:\n";
    for (auto it = graph.nbegin(0); it != graph.nend(0); ++it) {
        std::cout << "  -> " << graph.getvertexlabel(it.neighborid())
            << " with weight " << it.edgelabel() << "\n";
    }

    if (!graph.removeedge(0, 1)) {
        std::cout << "Failed to remove edge\n";
        return;
    }

    if (graph.hasedge(0, 1)) {
        std::cout << "Test failed: edge should be removed\n";
        return;
    }

    size_t newVertex = graph.addvertex();
    if (!graph.setvertlabel(newVertex, "D")) {
        std::cout << "Failed to set vertex label\n";
        return;
    }

    if (graph.countvert() != 4) {
        std::cout << "Test failed: vertex add failed\n";
        return;
    }

    graph.addedge(3, 0, 7);
    if (!graph.setedgelabel(3, 0, 8)) {
        std::cout << "Failed to set edge label\n";
        return;
    }

    if (graph.getedgelabel(3, 0) != 8) {
        std::cout << "Test failed: edge label update failed\n";
        return;
    }

    if (!graph.removevertex(1)) {
        std::cout << "Failed to remove vertex\n";
        return;
    }

    if (graph.countvert() != 3) {
        std::cout << "Test failed: vertex remove failed\n";
        return;
    }

    auto labels = graph.getallvertexlabels();
    std::cout << "Vertex labels: ";
    for (size_t i = 0; i < labels.size(); ++i) {
        std::cout << labels[i] << " ";
    }
    std::cout << "\n";

    MyGraph graph2 = graph;
    if (graph2.countvert() != graph.countvert()) {
        std::cout << "Test failed: copy constructor failed\n";
        return;
    }

    MyGraph graph3;
    graph3 = graph;
    if (graph3.countvert() != graph.countvert()) {
        std::cout << "Test failed: assignment operator failed\n";
        return;
    }

    std::cout << "All graph tests passed!\n\n";
}

void testIterator() {
    std::cout << "Testing graph iterator...\n";

    MyGraph graph(4);
    graph.setvertlabel(0, "A");
    graph.setvertlabel(1, "B");
    graph.setvertlabel(2, "C");
    graph.setvertlabel(3, "D");

    graph.addedge(0, 1, 1);
    graph.addedge(0, 2, 2);
    graph.addedge(0, 3, 3);
    graph.addedge(1, 2, 4);

    int neighborCount = 0;
    for (auto it = graph.nbegin(0); it != graph.nend(0); ++it) {
        neighborCount++;
        std::cout << "Neighbor " << neighborCount << ": "
            << graph.getvertexlabel(it.neighborid())
            << " (weight: " << it.edgelabel() << ")\n";
    }

    if (neighborCount != 3) {
        std::cout << "Test failed: wrong number of neighbors\n";
        return;
    }

    neighborCount = 0;
    for (auto it = graph.nbegin(2); it != graph.nend(2); ++it) {
        neighborCount++;
    }

    if (neighborCount != 0) {
        std::cout << "Test failed: vertex 2 should have 0 outgoing edges\n";
        return;
    }

    std::cout << "Iterator tests passed!\n\n";
}

int main() {
    std::cout << "=== Graph Library Tests ===\n\n";

    testGraphOperations();
    testIterator();

    std::cout << "=== All tests completed successfully ===\n";

    return 0;
}