#include <iostream>
#include "graph.h"

typedef Graph<std::string, int> MyGraph;

int main()
{
    MyGraph graph(3);

    // Проверим количество вершин
    if (graph.VertexCount() != 3) {
        std::cout << "Недопустимое начальное количество вершин\n";
        return 1;
    }

    // Добавим вершину
    graph.AddVertex();
    if (graph.VertexCount() != 4) {
        std::cout << "Не удалось добавить вершину\n";
        return 1;
    }

    // Установим пометки для вершин
    graph.SetVertexLabel(0, "A");
    graph.SetVertexLabel(1, "B");

    auto label0 = graph.GetVertexLabel(0);
    auto label1 = graph.GetVertexLabel(1);

    if (!label0.has_value() || label0.value() != "A") {
        std::cout << "Неверная метка для вершины 0\n";
        return 1;
    }

    if (!label1.has_value() || label1.value() != "B") {
        std::cout << "Неверная метка для вершины 1\n";
        return 1;
    }

    // Добавим рёбра
    std::cout << "Добавляем ребро 0 -> 1 с весом 100\n";
    graph.AddEdge(0, 1, 100);
    std::cout << "Добавляем ребро 0 -> 2 с весом 200\n";
    graph.AddEdge(0, 2, 200);

    if (!graph.HasEdge(0, 1)) {
        std::cout << "Ребро 0->1 не добавлено\n";
        return 1;
    }

    if (!graph.HasEdge(0, 2)) {
        std::cout << "Ребро 0->2 не добавлено\n";
        return 1;
    }

    // Проверим пометки рёбер
    auto edgeLabel = graph.GetEdgeLabel(0, 1);
    if (!edgeLabel.has_value() || edgeLabel.value() != 100) {
        std::cout << "Неверная метка ребра для 0->1\n";
        return 1;
    }

    // Изменим пометку ребра
    graph.SetEdgeLabel(0, 1, 150);
    edgeLabel = graph.GetEdgeLabel(0, 1);
    if (!edgeLabel.has_value() || edgeLabel.value() != 150) {
        std::cout << "Не удалось обновить метку ребра для 0->1\n";
        return 1;
    }

    // Проверим соседей вершины
    auto neighbors = graph.GetNeighbors(0);
    size_t neighborCount = neighbors.size();
    if (neighborCount != 2) {
        std::cout << "Недопустимое количество соседей для вершины 0\n";
        return 1;
    }

    for (size_t i = 0; i < neighborCount; ++i) {
        size_t neighbor = neighbors.get(i);
        if (neighbor != 1 && neighbor != 2) {
            std::cout << "Найден неверный сосед: " << neighbor << "\n";
            return 1;
        }
    }

    // Удалим ребро
    std::cout << "Удаляем ребро 0 -> 1\n";
    graph.RemoveEdge(0, 1);
    if (graph.HasEdge(0, 1)) {
        std::cout << "Не удалось удалить ребро 0->1\n";
        return 1;
    }

    // Удалим вершину
    std::cout << "Удаляем вершину 2\n";
    graph.RemoveVertex(2);
    if (graph.VertexCount() != 3) {
        std::cout << "Не удалось удалить вершину 2\n";
        return 1;
    }

    std::cout << "Все тесты прошли успешно!\n";
    return 0;
}
