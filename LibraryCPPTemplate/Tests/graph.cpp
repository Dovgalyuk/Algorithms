#include "graph.h"
#include <iostream>
#include <set>

int main() {
    Graph<std::string, std::string> graph(5);

    graph.setVertexLabel(0, "A");
    graph.setVertexLabel(1, "B");
    graph.setVertexLabel(2, "C");
    graph.setVertexLabel(3, "D");
    graph.setVertexLabel(4, "E");

    if (graph.getVertexCount() != 5) {
        std::cout << "Invalid vertex amount" << std::endl;
        return 1;
    } else {
        std::cout << "Correct number of vertices" << std::endl;
    }

    graph.addEdge(0, 1, "m");
    graph.addEdge(1, 2, "f");
    graph.addEdge(2, 3, "s");
    graph.addEdge(1, 3, "o");
    graph.addEdge(3, 0, "t");
    graph.addEdge(3, 4, "e");

    for (size_t vertex = 0; vertex < graph.getVertexCount(); ++vertex) {
        Graph<std::string, std::string>::Iterator it = graph.getIterator(vertex);
        std::set<int> actual;

        while (it.hasNext()) {
            actual.insert((int)it.next());
        }

        std::set<int> expected;

        if (vertex == 0) {
            expected = { 1 }; 
        } else if (vertex == 1) {
            expected = { 2, 3 }; 
        } else if (vertex == 2) {
            expected = { 3 }; 
        } else if (vertex == 3) {
            expected = { 0, 4 }; 
        } else if (vertex == 4) {
            expected = {}; 
        }

        if (actual == expected) {
            std::cout << "Test passed for vertex " << vertex << ": ";
            for (int v : actual) {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "Test failed for vertex " << vertex << ": expected { ";
            for (int v : expected) {
                std::cout << v << " ";
            }
            std::cout << "} but got { ";
            for (int v : actual) {
                std::cout << v << " ";
            }
            std::cout << "}" << std::endl;
            return 1;
        }
    }

    graph.removeEdge(1, 2);
    for (size_t vertex = 0; vertex < graph.getVertexCount(); ++vertex) {
        Graph<std::string, std::string>::Iterator it = graph.getIterator(vertex);
        std::set<int> actual;

        while (it.hasNext()) {
            actual.insert((int)it.next());
        }

        std::set<int> expected;

        if (vertex == 0) {
            expected = { 1 }; 
        } else if (vertex == 1) {
            expected = { 3 }; 
        } else if (vertex == 2) {
            expected = { 3 }; 
        } else if (vertex == 3) {
            expected = { 0, 4 }; 
        } else if (vertex == 4) {
            expected = {}; 
        }

        if (actual == expected) {
            std::cout << "Post-removal test passed for vertex " << vertex << ": ";
            for (int v : actual) {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "Post-removal test failed for vertex " << vertex << ": expected { ";
            for (int v : expected) {
                std::cout << v << " ";
            }
            std::cout << "} but got { ";
            for (int v : actual) {
                std::cout << v << " ";
            }
            std::cout << "}" << std::endl;
            return 1;
        }
    }

    int index1 = 3;
    std::cout << "Deleting a vertex with index: " << index1 << std::endl;
    graph.removeVertex(index1);

    if (graph.getVertexCount() != 4) {
        std::cout << "Invalid vertex deletion" << std::endl;
        return 1;
    } else {
        std::cout << "Valid vertex removal" << std::endl;
    }

    return 0;
}
