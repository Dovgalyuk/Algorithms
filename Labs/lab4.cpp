#include <iostream>
#include <climits>
#include "graph.h"
#include <cassert>

const int INF = INT_MAX;

// Шаблонная функция для алгоритма Флойда
template<typename Data>
void modifiedFloydWarshall(const Graph<Data>& graph, size_t vertex_amount) {
    
    Graph<Data> mutableGraph = graph;

    // Итерация по всем вершинам
    for (size_t k = 0; k < vertex_amount; ++k) {
        for (size_t i = 0; i < vertex_amount; ++i) {
            for (size_t j = 0; j < vertex_amount; ++j) {
                // Получаем вес ребра между текущей вершиной и соседней вершиной
                typename Graph<Data>::Edge* edgeIK = mutableGraph.getEdge(i, k);
                typename Graph<Data>::Edge* edgeKJ = mutableGraph.getEdge(k, j);

                // Проверяем, что рёбра существуют
                if (edgeIK && edgeKJ) {
                    int weightIK = edgeIK->getEdgeData();
                    int weightKJ = edgeKJ->getEdgeData();

                    // Если сумма веса ребра от текущей вершины до соседней и веса ребра от соседней
                    // вершины до целевой больше, чем известный вес от текущей вершины до целевой,
                    // то обновляем значение веса от текущей вершины до целевой
                    if (mutableGraph.getVertex(i)->getVertexData() != INF &&
                        mutableGraph.getVertex(k)->getVertexData() != INF &&
                        mutableGraph.getVertex(j)->getVertexData() != INF &&
                        mutableGraph.getVertex(i)->getVertexData() + weightIK + weightKJ >
                        mutableGraph.getVertex(j)->getVertexData()) {
                        mutableGraph.getVertex(j)->setVertexData(
                                mutableGraph.getVertex(i)->getVertexData() + weightIK + weightKJ);
                    }
                }
            }
        }
    }

    // Вывод матрицы смежности
    std::cout << "Adjacency Matrix:\n";
    for (size_t i = 0; i < vertex_amount; ++i) {
        for (size_t j = 0; j < vertex_amount; ++j) {
            if (mutableGraph.getEdge(i, j)) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }

    // Вывод длиннейшего из кратчайших путей
    size_t start_vertex = 0;
    size_t end_vertex = vertex_amount - 1; 
    if (mutableGraph.getVertex(end_vertex)->getVertexData() != INF) {
        std::cout << "Longest path from vertex " << start_vertex << " to vertex " << end_vertex << " is "
                  << mutableGraph.getVertex(end_vertex)->getVertexData() << "\n";
    } else {
        std::cout << "Longest path from vertex " << start_vertex << " to vertex " << end_vertex << " is NULL\n";
    }
}

int main() {
    size_t vertex_amount = 0; 
    int N = 0; 

    
    std::cout << "Input vertex_amount> ";
    std::cin >> vertex_amount;
   
    Graph<int> graph(vertex_amount, 0);

    
    std::cout << "Input size read data> ";
    std::cin >> N;

    
    for (int i = 0; i < N; i++) {
        size_t start_vertex_index, end_vertex_index;
        int edge_data;
        std::cout << "input " << i << " data (size_t start_vertex_index, size_t end_vertex_index, Data edge_data)> ";
        std::cin >> start_vertex_index >> end_vertex_index >> edge_data;
        graph.addEdge(start_vertex_index, end_vertex_index, edge_data);
    }

    // Запуск алгоритма Флойда 
    modifiedFloydWarshall(graph, vertex_amount);

    return 0;
}