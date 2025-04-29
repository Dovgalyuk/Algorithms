#include <iostream>
#include <fstream>
#include <climits>
#include "graph.h"

template<typename Data>
void modifiedFloydWarshall(Graph<Data>& graph, size_t vertex_amount) {
    Graph<Data> mutableGraph = graph;

    for (size_t k = 0; k < vertex_amount; ++k) {
        for (size_t i = 0; i < vertex_amount; ++i) {
            for (size_t j = 0; j < vertex_amount; ++j) {
                if (mutableGraph.isEdgeExist(i, k) && mutableGraph.isEdgeExist(k, j)) {
                    Data weightIK = mutableGraph.getEdgeData(i, k);
                    Data weightKJ = mutableGraph.getEdgeData(k, j);

                    if (!mutableGraph.isEdgeExist(i, j) || mutableGraph.getEdgeData(i, j) < weightIK + weightKJ) {
                        mutableGraph.addEdge(i, j, weightIK + weightKJ);
                    }
                }
            }
        }
    }

    std::cout << "Матрица смежности (1 — если ребро существует, 0 — если нет ребра):\n";
    for (size_t i = 0; i < vertex_amount; ++i) {
        for (size_t j = 0; j < vertex_amount; ++j) {
            if (mutableGraph.isEdgeExist(i, j)) {
                std::cout << "1 ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }

    size_t start_vertex = 0;
    size_t end_vertex = vertex_amount - 1;
    if (mutableGraph.isEdgeExist(start_vertex, end_vertex)) {
        std::cout << "Самый длинный кратчайший путь от вершины " << start_vertex << " до вершины " << end_vertex << " равен "
                  << mutableGraph.getEdgeData(start_vertex, end_vertex) << "\n";
    } else {
        std::cout << "Путь между вершинами " << start_vertex << " и " << end_vertex << " не существует\n";
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    size_t vertex_amount = 0;
    int N = 0;
    Graph<int> graph;

    if (argc > 1) {
        std::ifstream infile(argv[1]);
        if (infile) {
            infile >> vertex_amount >> N;
            for (int i = 0; i < N; i++) {
                size_t start_vertex_index, end_vertex_index;
                int edge_data;
                infile >> start_vertex_index >> end_vertex_index >> edge_data;
                graph.addEdge(start_vertex_index, end_vertex_index, edge_data);
            }
            infile.close();
            std::cout << "Данные прочитаны из файла: " << argv[1] << "\n";
        } else {
            std::cerr << "Файл не найден. Переходим к ручному вводу.\n";
            std::cout << "Введите количество вершин> ";
            std::cin >> vertex_amount;

            std::cout << "Введите количество данных для чтения> ";
            std::cin >> N;

            for (int i = 0; i < N; i++) {
                size_t start_vertex_index, end_vertex_index;
                int edge_data;
                std::cout << "Введите " << i << " данные (size_t start_vertex_index, size_t end_vertex_index, Data edge_data)> ";
                std::cin >> start_vertex_index >> end_vertex_index >> edge_data;
                graph.addEdge(start_vertex_index, end_vertex_index, edge_data);
            }
        }
    } else {
        std::cout << "Введите количество вершин> ";
        std::cin >> vertex_amount;

        std::cout << "Введите количество данных для чтения> ";
        std::cin >> N;

        for (int i = 0; i < N; i++) {
            size_t start_vertex_index, end_vertex_index;
            int edge_data;
            std::cout << "Введите " << i << " данные (size_t start_vertex_index, size_t end_vertex_index, Data edge_data)> ";
            std::cin >> start_vertex_index >> end_vertex_index >> edge_data;
            graph.addEdge(start_vertex_index, end_vertex_index, edge_data);
        }
    }

    std::cout << "Исходный граф:\n";
    graph.printGraph();

    modifiedFloydWarshall(graph, vertex_amount);

    return 0;
}
