#include <iostream>
#include "graph.h"
#include "vector.h"
#include <algorithm>


int main() {
    Graph<int, int> graph(7);

    //test 1.get all vertex marks
    Vector<int> vertices = graph.getAllVertexMarks();
    if (7 != vertices.size()) {
        for (size_t i = 0; i < vertices.size(); ++i) {
            std::cout << vertices.get(i) << " ";
        }
        std::cout << "\ntest1.Incorrect graph\n";
        return 1;
    }

    //test 2. Removing vertex
    graph.removeVertex(6);
    Vector<int> vertices2 = graph.getAllVertexMarks();
    if (vertices2.size() != 6) {
        for (size_t i = 0; i < vertices2.size(); ++i) {
            std::cout << vertices2.get(i) << " ";
        }
        std::cout << "\ntest2.Incorrect graph\n";
        return 1;
    }

    //test 3.Adding vertex
    graph.addVertex();
    Vector<int> vertices3 = graph.getAllVertexMarks();
    if (vertices3.size() != 7) {
        for (size_t i = 0; i < vertices3.size(); ++i) {
            std::cout << vertices3.get(i) << " ";
        }
        std::cout << "\ntest3.Incorrect graph\n";
        return 1;
    }

    //test 4.Adding edge
    graph.addVertex();
    graph.addEdge(7, 4, 10);
    graph.addEdge(7, 1, 7);
    graph.addEdge(7, 2, 255);

    if (!graph.hasEdge(7, 4)) {
        std::cout << "\ntest4.Graph doesn't have 7 to 4 edge\n";
        for (auto i = graph.begin(7); i != graph.end(7); ++i) {
            std::cout << "To: " << (*i).path << " Mark: " << (*i).sign << '\n';
        }
        return 1;
    }
    if (!graph.hasEdge(7, 1)) {
        std::cout << "\ntest4.Graph doesn't have 7 to 1 edge\n";
        for (auto i = graph.begin(7); i != graph.end(7); ++i) {
            std::cout << "To: " << (*i).path << " Mark: " << (*i).sign << '\n';
        }
        return 1;
    }
    if (!graph.hasEdge(7, 2)) {
        std::cout << "\ntest4.Graph doesn't have 7 to 2 edge\n";
        for (auto i = graph.begin(7); i != graph.end(7); ++i) {
            std::cout << "To: " << (*i).path << " Mark: " << (*i).sign << '\n';
        }
        return 1;
    }

    //test 5.removing edge
    graph.removeEdge(7, 1);
    if (graph.hasEdge(7, 1)) {
        std::cout << "\ntest5.Graph hasn't 7 to 1 edge\n";
        for (auto i = graph.begin(7); i != graph.end(7); ++i) {
            std::cout << "To: " << (*i).path << " Mark: " << (*i).sign << std::endl;
        }
        return 1;
    }

    //test 6.setting edge sign
    graph.addVertex();
    graph.addEdge(1, 2, 1000);
    graph.setEdgeMark(1, 2, 1000);
    if (graph.getEdgeMark(1, 2) != 1000) {
        std::cout << "\ntest7. Graph edge sign. \n";
        return 1;
    }

    //test 7. getting vertex sign
    graph.setVertexMark(5, 11);
    if (graph.getVertexMark(5) != 11) {
        std::cout << "test8.Graph vertex sign.\n";
        return 1;
    }

    //test 8. getting size
    if (graph.getSize() != 9) {
        std::cout << "test9.Graph size.\n";
        return 1;
    }

    std::cout << "all tests passed. success.\n";
    return 0;
}
