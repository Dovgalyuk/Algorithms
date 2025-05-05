#include <iostream>
#include <climits>
#include "graph.h"
#include <cassert>

const int INF = INT_MAX;

template<typename Data>
void modifiedFloydWarshall(Graph<Data>& graph, size_t vertex_amount) {
    Graph<Data> mutableGraph = graph;

    for (size_t k = 0; k < vertex_amount; ++k) {
        for (size_t i = 0; i < vertex_amount; ++i) {
            for (size_t j = 0; j < vertex_amount; ++j) {
                typename Graph<Data>::Edge* edgeIK = mutableGraph.getEdge(i, k);
                typename Graph<Data>::Edge* edgeKJ = mutableGraph.getEdge(k, j);

                if (edgeIK && edgeKJ) {
                    int weightIK = edgeIK->getEdgeData();
                    int weightKJ = edgeKJ->getEdgeData();

                    // Обновляем вес рёбер на основе Флойда-Уоршелла
                    if (mutableGraph.getEdge(i, j) == nullptr || 
                        (weightIK != INF && weightKJ != INF && 
                         mutableGraph.getEdge(i, j)->getEdgeData() != INF &&
                         mutableGraph.getEdge(i, j)->getEdgeData() > weightIK + weightKJ)) {
                        if (mutableGraph.getEdge(i, j) == nullptr) {
                            mutableGraph.addEdge(i, j, weightIK + weightKJ);
                        } else {
                            mutableGraph.getEdge(i, j)->setEdgeData(weightIK + weightKJ);
                        }
                    }
                }
            }
        }
    }

    // Выводим матрицу смежности
    std::cout << "Adjacency Matrix:\n";
    for (size_t i = 0; i < vertex_amount; ++i) {
        for (size_t j = 0; j < vertex_amount; ++j) {
            if (mutableGraph.getEdge(i, j)) {
                std::cout << "1 "; // Есть ребро
            } else {
                std::cout << "0 "; // Нет рёбер
            }
        }
        std::cout << "\n";
    }

    // Для примера выводим кратчайший путь от первой вершины к последней
    size_t start_vertex = 0;
    size_t end_vertex = vertex_amount - 1; 
    if (mutableGraph.getEdge(start_vertex, end_vertex) != nullptr) {
        std::cout << "Shortest path from vertex " << start_vertex << " to vertex " << end_vertex << " is "
                  << mutableGraph.getEdge(start_vertex, end_vertex)->getEdgeData() << "\n";
    } else {
        std::cout << "No path from vertex " << start_vertex << " to vertex " << end_vertex << "\n";
    }
}

int main() {
    size_t vertex_amount = 0; 
    int N = 0; 

    std::cout << "Input vertex_amount> ";
    std::cin >> vertex_amount;

    // Инициализация графа
    Graph<int> graph(vertex_amount);

    std::cout << "Input number of edges> ";
    std::cin >> N;

    // Ввод рёбер
    for (int i = 0; i < N; i++) {
        size_t start_vertex_index, end_vertex_index;
        int edge_data;
        std::cout << "Input " << i << " data (size_t start_vertex_index, size_t end_vertex_index, Data edge_data)> ";
        std::cin >> start_vertex_index >> end_vertex_index >> edge_data;
        graph.addEdge(start_vertex_index, end_vertex_index, edge_data);
    }

    // Запуск модифицированного алгоритма Флойда-Уоршелла
    modifiedFloydWarshall(graph, vertex_amount);

    return 0;
}
