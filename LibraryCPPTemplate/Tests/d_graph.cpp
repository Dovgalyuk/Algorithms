#include <iostream>
#include "d_graph.h"

using namespace std;

int main() {
    const int vertexCount = 10;
    auto graph = d_graph<int>(10);

    for (int i = 0; i < vertexCount; i++) {
        graph.getVertex(i)->data = i;
        if (graph.getVertex(i)->data != i) {
            cout << "Adding a vertex to the graph does not work correctly.";
            return 0;
        }
    }

    graph.getVertex(9)->data = 11;

    if (graph.getVertex(9)->data != 11) {
        cout << "Modifying the vertex data does not work correctly.";
        return 0;
    }


    graph.setEdgeVertices(graph.getVertex(1), 2, 10);

    if (!graph.checkEdge(1, 2)) {
        std::cout << "Adding a edge to the graph does not work correctly.";
        return 0;
    }

    graph.removeVertex(1);

    if (graph.checkEdge(1, 2)) {
        cout << "Deleting a rebro from the graph does not work correctly.";
        return 0;
    }

    graph.setEdgetoVertex(0, 1, 1);
    graph.setEdgetoVertex(0, 3, 7);
    graph.setEdgetoVertex(0, 4, 20);
    graph.setEdgetoVertex(1, 7, 2);
    graph.setEdgetoVertex(3, 0, 39);
    graph.setEdgetoVertex(3, 2, 419);

    d_graph<int>::EdgesIterator iterator(graph, graph.getVertex(0));
    int check = 0;
    if (*iterator != graph.getVertex(0)) {
        cout << "The vertex iterator does not work correctly.";
    }
    while (++iterator) {
        check++;    
    }

    if (check != 3) {
        cout << "The vertex iterator does not work correctly.";
        return 0;
    }

    return 0;
}