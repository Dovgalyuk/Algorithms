#include <iostream>
#include "graph.h"

typedef Graph<int, int> MyGraph;

int main() {
    MyGraph *graph = new MyGraph;

    // ������������ ���������� ������
    auto v1 = graph->addVertex(1);
    auto v2 = graph->addVertex(2);
    auto v3 = graph->addVertex(3);

    if (graph->vertexCount() != 3) {
        std::cout << "Error in addVertex or vertexCount\n";
        return 1;
    }

    // ������������ ���������� ����
    graph->addEdge(v1, v2, 10);
    graph->addEdge(v2, v3, 20);

    if (!graph->edgeExists(v1, v2) || !graph->edgeExists(v2, v3)) {
        std::cout << "Error in addEdge or edgeExists\n";
        return 1;
    }
    // ������������ ��������� �������
    MyGraph::NeighborIterator it(v2);
    while (it.hasNext()) {
        auto neighbor = it.next().neighbor;
        if (graph->getVertexData(neighbor) != 3)
        {
            std::cout << "Error in Neighbors of Vertex\n";
            return 1;
        }
    }
    std::cout << "\n";

    // ������������ �������� �����
    graph->removeEdge(v1,v2);
    if (graph->edgeExists(v1, v2)) {
        std::cout << "Error in removeEdge\n";
        return 1;
    }

    // ������������ �������� �������
    graph->removeVertex(v3);
    if (graph->vertexCount() != 2) {
        std::cout << "Error in removeVertex\n";
        return 1;
    }
    const int additionalVertexCount = 10;
    MyGraph::Vertex* additionalVertices[additionalVertexCount];

    // �������� �������������� ������
    for (int i = 0; i < additionalVertexCount; ++i) {
        additionalVertices[i] = graph->addVertex(i + 4);
    }

    // �������� �������������� ����
    for (int i = 0; i < additionalVertexCount; ++i) {
        graph->addEdge(additionalVertices[i], additionalVertices[(i + 1) % additionalVertexCount], (i + 4) * 10);
    }

    // �������� ������������� �������������� ����
    for (int i = 0; i < additionalVertexCount; ++i) {
        if (!graph->edgeExists(additionalVertices[i], additionalVertices[(i + 1) % additionalVertexCount])) {
            std::cout << "Error in addEdge or edgeExists for additional vertices\n";
            return 1;
        }
    }

    // �������� �������������� ����
    for (int i = 0; i < additionalVertexCount; ++i) {
        graph->removeEdge(additionalVertices[i], additionalVertices[(i + 1) % additionalVertexCount]);
    }

    // �������� ���������� �������������� ����
    for (int i = 0; i < additionalVertexCount; ++i) {
        if (graph->edgeExists(additionalVertices[i], additionalVertices[(i + 1) % additionalVertexCount])) {
            std::cout << "Error in removeEdge for additional vertices\n";
            return 1;
        }
    }

    delete graph;
}