#include "graph.h"
#include <iostream>

int main() {
    Graph *g = new Graph;

    // ���������� ������
    g->addVertex(1);
    g->addVertex(2);
    g->addVertex(3);

    // ���������� ����
    g->addEdge(1, 2);
    g->addEdge(2, 3);

    // �������� ������� �����
    if (g->edgeExists(1, 2) && g->edgeExists(2, 3) && !g->edgeExists(1, 3)) {
        std::cout << "Edge existence check passed." << std::endl;
    }
    else {
        std::cout << "Edge existence check failed." << std::endl;
    }

    // ��������� � ��������� ������� ��� ������ � ����
    g->setVertexMark(1, "A");
    g->setEdgeMark(1, 2, "edge1");
    if (g->getVertexMark(1) == "A" && g->getEdgeMark(1, 2) == "edge1") {
        std::cout << "Vertex and edge mark check passed." << std::endl;
    }
    else {
        std::cout << "Vertex and edge mark check failed." << std::endl;
    }

    // ������������� NeighborIterator
    Graph::NeighborIterator it = g->getNeighbors(2);
    std::cout << "Neighbors of vertex 2: ";
    while (it.hasNext()) {
        Graph::Vertex* v = it.next();
        std::cout << v->id << " ";
    }
    std::cout << std::endl;

    // �������� ������� � �����
    g->removeEdge(1, 2);
    g->removeVertex(3);

    // �������� ��������
    if (!g->edgeExists(1, 2) && g->getVertexMark(3) == "") {
        std::cout << "Vertex and edge removal check passed." << std::endl;
    }
    else {
        std::cout << "Vertex and edge removal check failed." << std::endl;
    }

    return 0;
}