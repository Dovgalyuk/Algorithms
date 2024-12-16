#include <iostream>
#include <cassert>
#include "graph.h"

void test_graph() {
    // Создаем граф с 5 вершинами
    Graph<int, std::string> g(5);

    // Добавляем вершины
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);

    // Добавляем ребра
    g.addEdge(0, 1, "Edge 0-1");
    g.addEdge(1, 2, "Edge 1-2");
    g.addEdge(2, 3, "Edge 2-3");
    g.addEdge(3, 4, "Edge 3-4");
    g.addEdge(4, 0, "Edge 4-0");

    // Проверяем существование ребер
    assert(g.hasEdge(0, 1));
    assert(g.hasEdge(1, 2));
    assert(g.hasEdge(2, 3));
    assert(g.hasEdge(3, 4));
    assert(g.hasEdge(4, 0));
    assert(!g.hasEdge(0, 2));

    // Проверяем пометки ребер
    assert(g.getEdgeLabel(0, 1) == "Edge 0-1");
    assert(g.getEdgeLabel(1, 2) == "Edge 1-2");
    assert(g.getEdgeLabel(2, 3) == "Edge 2-3");
    assert(g.getEdgeLabel(3, 4) == "Edge 3-4");
    assert(g.getEdgeLabel(4, 0) == "Edge 4-0");

    // Проверяем пометки вершин
    assert(g.getVertexLabel(0) == 1);
    assert(g.getVertexLabel(1) == 2);
    assert(g.getVertexLabel(2) == 3);
    assert(g.getVertexLabel(3) == 4);
    assert(g.getVertexLabel(4) == 5);

    // Проверяем получение всех пометок вершин
    std::vector<int> labels = g.getAllVertexLabels();
    assert(labels.size() == 5);
    assert(labels[0] == 1);
    assert(labels[1] == 2);
    assert(labels[2] == 3);
    assert(labels[3] == 4);
    assert(labels[4] == 5);

    // Проверяем итератор для перебора соседей
    auto it = g.neighborsBegin(0);
    assert(it != g.neighborsEnd(0));
    assert((*it).first == 1);
    assert((*it).second == "Edge 0-1");
    ++it;
    assert(it == g.neighborsEnd(0));

    // Удаляем ребро и проверяем
    g.removeEdge(0, 1);
    assert(!g.hasEdge(0, 1));

    // Удаляем вершину и проверяем
    g.removeVertex(2);
    assert(g.getAllVertexLabels().size() == 4);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test_graph();
    return 0;
}
