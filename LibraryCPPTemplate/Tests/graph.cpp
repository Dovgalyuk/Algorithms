#include <iostream>
#include "graph.h"
#include "vector.h"
#include <algorithm>

typedef Graph<int, int> MyGraph;

int main() {
    MyGraph graph(7);

    // Test 1: get all vertex marks
    Vector<int> vertices = graph.getAllVertexMarks();
    if (7 != vertices.size()) {
        for (size_t i = 0; i < vertices.size(); ++i) {
            std::cout << vertices.get(i) << " ";
        }
        std::cout << "\nTest1: Incorrect graph\n";
        return 1;
    }

    // Test 2: Removing vertex
    graph.removeVertex(6);
    Vector<int> vertices2 = graph.getAllVertexMarks();
    if (vertices2.size() != 6) {
        for (size_t i = 0; i < vertices2.size(); ++i) {
            std::cout << vertices2.get(i) << " ";
        }
        std::cout << "\nTest2: Incorrect graph\n";
        return 1;
    }

    // Test 3: Adding vertex
    graph.addVertex();
    Vector<int> vertices3 = graph.getAllVertexMarks();
    if (vertices3.size() != 7) {
        for (size_t i = 0; i < vertices3.size(); ++i) {
            std::cout << vertices3.get(i) << " ";
        }
        std::cout << "\nTest3: Incorrect graph\n";
        return 1;
    }

    // Test 4: Adding edge
    graph.addVertex();
    graph.addEdge(7, 4, 10);
    graph.addEdge(7, 1, 7);
    graph.addEdge(7, 2, 255);

    if (!graph.hasEdge(7, 4)) {
        std::cout << "\nTest4: Graph does not have 7 --> 4 edge\n";
        for (auto i = graph.begin(7); i != graph.end(7); ++i) {
            std::cout << "To: " << (*i).path << " Mark: " << (*i).sign << '\n';
        }
        return 1;
    }
    if (!graph.hasEdge(7, 1)) {
        std::cout << "\nTest4: Graph does not have 7 --> 1 edge\n";
        for (auto i = graph.begin(7); i != graph.end(7); ++i) {
            std::cout << "To: " << (*i).path << " Mark: " << (*i).sign << '\n';
        }
        return 1;
    }
    if (!graph.hasEdge(7, 2)) {
        std::cout << "\nTest4: Graph does not have 7 --> 2 edge\n";
        for (auto i = graph.begin(7); i != graph.end(7); ++i) {
            std::cout << "To: " << (*i).path << " Mark: " << (*i).sign << '\n';
        }
        return 1;
    }

    // Test 5: Removing edge
    graph.removeEdge(7, 1);
    if (graph.hasEdge(7, 1)) {
        std::cout << "\nTest5: Graph still has 10 --> 1 edge\n";
        for (auto i = graph.begin(10); i != graph.end(10); ++i) {
            std::cout << "To: " << (*i).path << " Mark: " << (*i).sign << std::endl;
        }
        return 1;
    }

    // Test 6: Removing vertex
    graph.addVertex();
    graph.addEdge(3, 4, -15);
    graph.removeVertex(7);
    if (!graph.hasEdge(3, 4)) {
        std::cout << "\nTest6: Graph does not have 3 --> 4 edge\n";
        for (auto it = graph.begin(3); it != graph.end(3); ++it) {
            std::cout << "To: " << (*it).path << " Mark: " << (*it).sign << std::endl;
        }
        return 1;
    }

    // Test 7: Setting edge sign
    graph.addVertex();
    graph.addEdge(1, 2, 1000);
    graph.setEdgeMark(1, 2, 1000);
    if (graph.getEdgeMark(1, 2) != 1000) {
        std::cout << "\nTest7: Graph edge sign: " << graph.getEdgeMark(1, 2) << '\n';
        return 1;
    }

    // Test 8: Getting vertex sign
    graph.setVertexMark(5, 11);
    if (graph.getVertexMark(5) != 11) {
        std::cout << "Test8: Graph vertex sign: " << graph.getVertexMark(9) << '\n';
        return 1;
    }

    std::cout << "All tests passed successfully!\n";
    return 0;
}
