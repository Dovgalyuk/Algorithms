#include <iostream>
#include "graph.h"

using namespace std;

template <typename Data, typename weight>
void inputTheVertexes(const int size_graph, Graph<Data, weight>* graph) {
    for (int i = 0; i < size_graph; ++i) {
        int tempData;
        cout << "[" << i << "] = ";
        cin >> tempData;
        graph->get_vertex(i)->set_data(tempData);
    }
    cout << "\n";
}

template <typename Data, typename weight>
void inputEdgesForVertexes(const int size_graph, Graph<Data, weight>* graph) {
    for (int i = 0; i < size_graph; i++) {
        cout << "\n";
        cout << "Вершина: " << graph->get_vertex_data(i) << " (Индекс: " << graph->find_index(graph->get_vertex(i)) << ")" << "\n";
        cout << "Сколько рёбер будет у вершины?\n> ";
        int tempCountEdges;
        cin >> tempCountEdges;
        cout << "\n";
        for (int j = 0; j < tempCountEdges; ++j) {
            cout << j + 1 << " Ребро. Введите индекс следующей вершины: ";
            int indexToVertex;
            cin >> indexToVertex;
            cout << "Введите вес: ";
            int tempWeight;
            cin >> tempWeight;
            graph->get_vertex(i)->add_edge(graph->get_vertex(indexToVertex), tempWeight);
        }
    }
}

int** initializationMatrix(const int size_graph) {
    int** shortest_path = new int* [size_graph];
    for (size_t i = 0; i < size_graph; i++) {
        shortest_path[i] = new int[size_graph];
    }
    for (int i = 0; i < size_graph; i++) {
        for (int j = 0; j < size_graph; j++) {
            shortest_path[i][j] = -5;
        }
    }
    return shortest_path;
}

template <typename Data, typename weight>
void setWeightInTheMatrix(const int size_graph, int** shortest_path, Graph<Data, weight>* graph) {
    // 'edge = -1' - path is not exist
    for (int i = 0; i < size_graph; ++i) {
        for (int j = 0; j < size_graph; ++j) {
            if (i == j) {
                //If the vertices are the same, then the cell is 0
                shortest_path[i][j] = 0;
            }
            else {
                //if the path exists, set the weight of its edge.
                if (!graph->check_edge_with_empty(graph->get_vertex(i), graph->get_vertex(j))) shortest_path[i][j] = graph->get_vertex(i)->get_edge(graph->get_vertex(j))->get_weight();
                //othersize, set -1
                else
                    shortest_path[i][j] = -1;
            }
        }
    }
}

//show the original matrix in the console
void showTheOriginalMatrix(const int size_graph, int** shortest_path) {
    cout << "\n";
    for (int i = 0; i < size_graph; i++) {
        for (int j = 0; j < size_graph; j++) {
            cout << shortest_path[i][j] << " ";
        }
        cout << "\n";
    }
}

//finding the shortest path using floyd's algorithm
void findTheShortestPath(const int size_graph, int** shortest_path) {
    for (int k = 0; k < size_graph; k++) {
        for (int i = 0; i < size_graph; i++) {
            for (int j = 0; j < size_graph; j++) {
                if (i != j && shortest_path[i][k] != -1 && shortest_path[k][j] != -1) {
                    if (shortest_path[i][j] == -1) {
                        shortest_path[i][j] = shortest_path[i][k] + shortest_path[k][j];
                    }
                    else {
                        shortest_path[i][j] = min(shortest_path[i][j], shortest_path[i][k] + shortest_path[k][j]);
                    }
                }
            }
        }
    }
}

template <typename Data, typename weight>
void showTheShortestPath(const int size_graph, int** shortest_path, Graph<Data, weight>* graph) {
    cout << "\n" << "shortest path:" << "\n";
    for (auto i = 0; i < size_graph; i++) {
        for (size_t j = 0; j < size_graph; j++) {
            cout << shortest_path[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n";
    for (size_t i = 0; i < size_graph; i++) {
        for (size_t j = 1; j < size_graph; j++) {
            if (shortest_path[i][j] > 0) cout << "Из вершины " << "'" << graph->get_vertex_data(i) << "'" << " в вершину " << "'" << graph->get_vertex_data(j) << "' = " << shortest_path[i][j] << "\n";
        }
    }
}

void program() {
    cout << "Введите количество вершин: ";
    int size_graph;
    cin >> size_graph;

    auto graph = new Graph<int, int>(0, size_graph);

    inputTheVertexes(size_graph, graph);

    inputEdgesForVertexes(size_graph, graph);

    int** shortest_path = initializationMatrix(size_graph);

    setWeightInTheMatrix(size_graph, shortest_path, graph);

    showTheOriginalMatrix(size_graph, shortest_path);

    findTheShortestPath(size_graph, shortest_path);

    showTheShortestPath(size_graph, shortest_path, graph);
}

int main() {
    setlocale(LC_ALL, "rus");

    try {
        program();
    }
    catch (const char* e) {
        cout << e << "\n\n";
    }
}