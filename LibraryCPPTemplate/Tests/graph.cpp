#include <iostream>
#include <cassert>
#include "graph.h"

void test_graph() {
    Graph<int, std::string> g(5);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addEdge(0, 1, "Ребро 0-1");
    g.addEdge(1, 2, "Ребро 1-2");
    g.addEdge(2, 3, "Ребро 2-3");
    g.addEdge(3, 4, "Ребро 3-4");
    g.addEdge(4, 0, "Ребро 4-0");

    if (!g.hasEdge(0, 1)) {
        std::cerr << "Тест провален: ребро (0, 1) не найдено" << std::endl;
    }
    if (!g.hasEdge(1, 2)) {
        std::cerr << "Тест провален: ребро (1, 2) не найдено" << std::endl;
    }
    if (!g.hasEdge(2, 3)) {
        std::cerr << "Тест провален: ребро (2, 3) не найдено" << std::endl;
    }
    if (!g.hasEdge(3, 4)) {
        std::cerr << "Тест провален: ребро (3, 4) не найдено" << std::endl;
    }
    if (!g.hasEdge(4, 0)) {
        std::cerr << "Тест провален: ребро (4, 0) не найдено" << std::endl;
    }
    if (g.hasEdge(0, 2)) {
        std::cerr << "Тест провален: ребро (0, 2) найдено" << std::endl;
    }
    if (g.getEdgeLabel(0, 1) != "Ребро 0-1") {
        std::cerr << "Тест провален: неверная метка ребра (0, 1)" << std::endl;
    }
    if (g.getEdgeLabel(1, 2) != "Ребро 1-2") {
        std::cerr << "Тест провален: неверная метка ребра (1, 2)" << std::endl;
    }
    if (g.getEdgeLabel(2, 3) != "Ребро 2-3") {
        std::cerr << "Тест провален: неверная метка ребра (2, 3)" << std::endl;
    }
    if (g.getEdgeLabel(3, 4) != "Ребро 3-4") {
        std::cerr << "Тест провален: неверная метка ребра (3, 4)" << std::endl;
    }
    if (g.getEdgeLabel(4, 0) != "Ребро 4-0") {
        std::cerr << "Тест провален: неверная метка ребра (4, 0)" << std::endl;
    }
    if (g.getVertexLabel(0) != 1) {
        std::cerr << "Тест провален: неверная метка вершины 0" << std::endl;
    }
    if (g.getVertexLabel(1) != 2) {
        std::cerr << "Тест провален: неверная метка вершины 1" << std::endl;
    }
    if (g.getVertexLabel(2) != 3) {
        std::cerr << "Тест провален: неверная метка вершины 2" << std::endl;
    }
    if (g.getVertexLabel(3) != 4) {
        std::cerr << "Тест провален: неверная метка вершины 3" << std::endl;
    }
    if (g.getVertexLabel(4) != 5) {
        std::cerr << "Тест провален: неверная метка вершины 4" << std::endl;
    }

    std::vector<int> labels = g.getAllVertexLabels();
    if (labels.size() != 5) {
        std::cerr << "Тест провален: неверное количество вершин" << std::endl;
    }
    if (labels[0] != 1) {
        std::cerr << "Тест провален: неверная метка вершины 0" << std::endl;
    }
    if (labels[1] != 2) {
        std::cerr << "Тест провален: неверная метка вершины 1" << std::endl;
    }
    if (labels[2] != 3) {
        std::cerr << "Тест провален: неверная метка вершины 2" << std::endl;
    }
    if (labels[3] != 4) {
        std::cerr << "Тест провален: неверная метка вершины 3" << std::endl;
    }
    if (labels[4] != 5) {
        std::cerr << "Тест провален: неверная метка вершины 4" << std::endl;
    }

    auto it = g.neighborsBegin(0);
    if (it == g.neighborsEnd(0)) {
        std::cerr << "Тест провален: нет соседей для вершины 0" << std::endl;
    }
    if ((*it).first != 1) {
        std::cerr << "Тест провален: неверный сосед для вершины 0" << std::endl;
    }
    if ((*it).second != "Ребро 0-1") {
        std::cerr << "Тест провален: неверная метка ребра (0, 1)" << std::endl;
    }
    ++it;
    if (it != g.neighborsEnd(0)) {
        std::cerr << "Тест провален: неверное количество соседей для вершины 0" << std::endl;
    }

    g.removeEdge(0, 1);
    if (g.hasEdge(0, 1)) {
        std::cerr << "Тест провален: ребро (0, 1) не удалено" << std::endl;
    }

    g.removeVertex(2);
    if (g.getAllVertexLabels().size() != 4) {
        std::cerr << "Тест провален: неверное количество вершин после удаления" << std::endl;
    }

    std::cout << "Все тесты прошли!" << std::endl;
}

int main() {
    test_graph();
    return 0;
}
