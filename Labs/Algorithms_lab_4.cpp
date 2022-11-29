#include <iostream>
#include "graph.h"

using namespace std;

template <typename Data, typename Weight>
void inputTheVertexes(const int size_graph, Graph<Data, Weight>* graph) {
    for (int i = 0; i < size_graph; ++i) {
        Data data;
        cout << "[" << i << "] = ";
        cin >> data;
        graph->get_vertex(i)->set_data(data);
    }
    cout << "\n";
}

template <typename Data, typename Weight>
void inputEdgesForVertexes(const int size_graph, Graph<Data, Weight>* graph) {
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
            Weight tempWeight;
            cin >> tempWeight;
            graph->get_vertex(i)->add_edge(graph->get_vertex(indexToVertex), tempWeight);
        }
    }
}

template <typename Data, typename Weight>
Data** initializationMatrix(const int size_graph) {
    Data** paths = new int* [size_graph];
    for (size_t i = 0; i < size_graph; i++) {
        paths[i] = new int[size_graph];
    }
    for (int i = 0; i < size_graph; i++) {
        for (int j = 0; j < size_graph; j++) {
            paths[i][j] = -5;
        }
    }
    return paths;
}

template <typename Data, typename Weight>
void setWeightInTheMatrix(const int size_graph, Data** paths, Graph<Data, Weight>* graph) {
    // 'edge = -1' - path is not exist
    for (int i = 0; i < size_graph; ++i) {
        for (int j = 0; j < size_graph; ++j) {
            if (i == j) {
                //If the vertices are the same, then the cell is 0
                paths[i][j] = 0;
            }
            else {
                //if the path exists, set the Weight of its edge.
                if (!graph->check_edge_with_empty(graph->get_vertex(i), graph->get_vertex(j))) paths[i][j] = graph->get_vertex(i)->get_edge(graph->get_vertex(j))->get_weight();
                //othersize, set -1
                else
                    paths[i][j] = -1;
            }
        }
    }
}

//show the original matrix in the console
template <typename Data, typename Weight>
void showTheOriginalMatrix(const int size_graph, Data** paths) {
    cout << "\n";
    for (int i = 0; i < size_graph; i++) {
        for (int j = 0; j < size_graph; j++) {
            cout << paths[i][j] << " ";
        }
        cout << "\n";
    }

    int index = 0;
    int data;
    List<int> list;
    for (size_t i = 0; i < size_graph; i++) {
        data = 100000;
        for (size_t j = 0; j <= size_graph; j++) {
            if (index == i && paths[i][j] > 0 && paths[i][j] < data) {
                data = paths[i][j];
                list.push_back(paths[i][j]);
                index = j;
            }
        }
    }
    for (auto item = list.first(); item; item = item->next()) {
        cout << item->data() << " ";
    }
    cout << "\n\n";
}

//finding the shortest path using floyd's algorithm
template <typename Data, typename Weight>
void findTheLongestTheShortestPath(const int size_graph, Data** paths) {
    int index = 0;
    for (int k = 0; k < size_graph; k++) {
        for (int i = 0; i < size_graph; i++) {
            for (int j = 0; j < size_graph; j++) {
                if (i != j && paths[i][k] != -1 && paths[k][j] != -1) {
                    if (paths[i][j] == -1) {
                        paths[i][j] = paths[i][k] + paths[k][j];
                    }
                    else {
                        paths[i][j] = min(paths[i][j], paths[i][k] + paths[k][j]);
                    }
                }
            }
        }
    }
}

template <typename Data, typename Weight>
void showTheLongestOfTheShortestPath(const int size_graph, Data** paths, Graph<Data, Weight>* graph) {
    int data = -1, index_i = 0, index_j = 0;
    for (size_t i = 0; i < size_graph; i++) {
        for (size_t j = 1; j < size_graph; j++) {
            if (paths[i][j] > 0 && paths[i][j] > data) {
                data = paths[i][j];
                index_i = i;
                index_j = j;
            }
        }
    }
    cout << "Самый длинный из кратчайших путей из вершины " << "'" << graph->get_vertex_data(index_i) << "'" << " в вершину " << "'" << graph->get_vertex_data(index_j) << "' = " << paths[index_i][index_j] << "\n";

    cout << "\n";
    for (auto i = 0; i < size_graph; i++) {
        for (size_t j = 0; j < size_graph; j++) {
            cout << paths[i][j] << " ";
        }
        cout << "\n";
    }
    
}

template <typename Data, typename Weight>
void program() {
    cout << "Введите количество вершин: ";
    int size_graph;
    cin >> size_graph;

    auto graph = new Graph<int, int>(0, size_graph);

    inputTheVertexes(size_graph, graph);

    inputEdgesForVertexes(size_graph, graph);

    Data** paths = initializationMatrix<Data, Weight>(size_graph);

    setWeightInTheMatrix(size_graph, paths, graph);

    showTheOriginalMatrix<int, int>(size_graph, paths);

    findTheLongestTheShortestPath<int, int>(size_graph, paths);

    showTheLongestOfTheShortestPath(size_graph, paths, graph);
}

int main() {
    setlocale(LC_ALL, "rus");

    try {
        program<int, int>();
    }
    catch (const char* e) {
        cout << e << "\n\n";
    }

    return 0;
}
