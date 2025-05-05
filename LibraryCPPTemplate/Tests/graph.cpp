#include <iostream>
#include "graph.h"

using namespace std;

typedef Graph<int> MyGraph;

int main() {
    MyGraph* graph = new MyGraph(6);

    if (graph->getVertexAmount() != 6) {
        cout << "Invalid vertex amount\n";
        return 1;
    }

    // Проверка данных вершин
    for (size_t i = 0; i < 6; i++) {
        if (graph->getVertex(i).getVertexData() != (int)i) {
            cout << "Invalid vertex data\n";
            return 1;
        }
    }

    // Добавление рёбер
    graph->addEdge(0, 3, 15);
    graph->addEdge(2, 1, 3);
    graph->addEdge(3, 4, 5);

    if (!graph->isEdgeExist(2, 1)) {
        cout << "Invalid edge creation\n";
        return 1;
    }

    // Итерация по графу
    auto it = graph->getIterator(0);
    while (*it) {
        cout << "Visiting vertex: " << it.getIndex() << endl;
        ++it;
    }

    // Получение данных рёбер
    if (graph->getEdge(2, 1)->getEdgeData() != 3) {
        cout << "Invalid edge data\n";
        return 1;
    }

    // Изменение данных рёбер
    graph->getEdge(0, 3)->setEdgeData(30);
    if (graph->getEdge(0, 3)->getEdgeData() != 30) {
        cout << "Invalid edge data setting\n";
        return 1;
    }

    // Удаление рёбер и проверка
    graph->removeEdge(2, 1);
    if (graph->isEdgeExist(2, 1)) {
        cout << "Invalid edge deletion\n";
        return 1;
    }

    // Удаление вершины и проверка
    graph->removeVertex(3);
    if (graph->getVertexAmount() != 5) {
        cout << "Invalid vertex deletion\n";
        return 1;
    }

    delete graph;  // Удаление графа
    return 0;
}
