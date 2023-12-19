#include <iostream>
#include "graph.h"

using namespace std;

typedef Graph<int> MyGraph;

const int INF = 999999; // Значение "бесконечности" для отсутствия ребра между вершинами

void floydWarshall(MyGraph* graph) {
    size_t vertex_count = graph->getVertexAmount();

    // Создаем матрицу для хранения длин кратчайших путей
    int** dist = new int* [vertex_count];
    for (size_t i = 0; i < vertex_count; ++i) {
        dist[i] = new int[vertex_count];
        for (size_t j = 0; j < vertex_count; ++j) {
            if (i == j) {
                dist[i][j] = 0; // Расстояние от вершины до самой себя равно 0
            }
            else if (graph->isEdgeExist(i, j)) {
                dist[i][j] = graph->getEdge(i, j)->getEdgeData(); // Установка известных расстояний
            }
            else {
                dist[i][j] = INF; // Инициализируем остальные расстояния как "бесконечность"
            }
        }
    }

    // Алгоритм Флойда
    for (size_t k = 0; k < vertex_count; ++k) {
        for (size_t i = 0; i < vertex_count; ++i) {
            for (size_t j = 0; j < vertex_count; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Вывод результатов
    cout << "Кратчайший путь между вершинами:\n";
    for (size_t i = 0; i < vertex_count; ++i) {
        for (size_t j = 0; j < vertex_count; ++j) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            }
            else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }

    // Освобождаем выделенную память для матрицы
    for (size_t i = 0; i < vertex_count; ++i) {
        delete[] dist[i];
    }
    delete[] dist;
}

int main() {
    setlocale(LC_ALL, "ru");
    size_t vertex_count;
    cout << "Введите количество вершин в графе: ";
    cin >> vertex_count;

    MyGraph* graph = new MyGraph(vertex_count, INF); // Создаем граф с заданным числом вершин и значениями "бесконечности"

    // Чтение параметров графа (рёбер)
    cout << "Введите данные о рёбрах для графика:\n";
    for (size_t i = 0; i < vertex_count; ++i) {
        for (size_t j = 0; j < vertex_count; ++j) {
            int edge_data;
            cin >> edge_data;
            if (edge_data != INF) {
                graph->addEdge(i, j, edge_data); // Добавление рёбер в граф
            }
        }
    }

    // Вызов функции для нахождения кратчайших путей
    floydWarshall(graph);

    delete graph; // Освобождение памяти, выделенной для графа
    return 0;
}