#include <iostream>
#include "graph.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    //input count vertexes
    cout << "Введите количество вершин: ";
    int size_graph;
    cin >> size_graph;

    //initialization graph
    auto graph = new Graph<int, int>(0, size_graph);

    //input data from the vertex
    for (int i = 0; i < size_graph; ++i) {
        int data;
        cout << "[" << i << "] = ";
        cin >> data;
        graph->get_vertex(i)->set_data(data);
    }
    cout << "\n";

    //input edges from the vertexes
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
            int tempSize;
            cin >> tempSize;
            graph->get_vertex(i)->add_edge(graph->get_vertex(indexToVertex), tempSize);
        }
    }

    //initialization matrix
    int** paths = new int* [size_graph];
    for (size_t i = 0; i < size_graph; i++) {
        paths[i] = new int[size_graph];
    }
    for (int i = 0; i < size_graph; i++) {
        for (int j = 0; j < size_graph; j++) {
            paths[i][j] = -5;
        }
    }

    // 'edge = -1' - path is not exist
    for (int i = 0; i < size_graph; ++i) {
        for (int j = 0; j < size_graph; ++j) {
            if (i == j) {
                //If the vertices are the same, then the cell is 0
                paths[i][j] = 0;
            }
            else {
                //if the path exists, set the Size of its edge.
                if (!graph->check_edge_with_empty(graph->get_vertex(i), graph->get_vertex(j))) paths[i][j] = graph->get_vertex(i)->get_edge(graph->get_vertex(j)).get_weight();
                //othersize, set -1
                else
                    paths[i][j] = -1;
            }
        }
    }

    //show initial matrix
    cout << "\n";
    for (int i = 0; i < size_graph; i++) {
        for (int j = 0; j < size_graph; j++) {
            cout << paths[i][j] << " ";
        }
        cout << "\n";
    }

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

    cout << "\nСамый длинный из кратчайших путей из вершины " << "'" << graph->get_vertex_data(index_i) << "'" << " в вершину " << "'" << graph->get_vertex_data(index_j) << "' = " << paths[index_i][index_j] << "\n";



    return 0;
}
