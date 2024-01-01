#include <iostream>
#include "graph.h"

using namespace std;

typedef Graph<int, int> MyGraph;

const int INF = 999999;

void floydWarshall(MyGraph& graph) {
    size_t vertex_count = graph.getVertexAmount();

    int** dist = new int* [vertex_count];
    for (size_t i = 0; i < vertex_count; ++i) {
        dist[i] = new int[vertex_count];
        for (size_t j = 0; j < vertex_count; ++j) {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (size_t i = 0; i < vertex_count; ++i) {
        MyGraph::Iterator it = graph.getIterator(i);
        while (*it) {
            size_t current_index = it.getIndex();
            MyGraph::Edge* edge = graph.getEdge(i, current_index);
            if (edge) {
                dist[i][current_index] = edge->getEdgeData();
            }
            ++it;
        }
    }

    for (size_t k = 0; k < vertex_count; ++k) {
        for (size_t i = 0; i < vertex_count; ++i) {
            for (size_t j = 0; j < vertex_count; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

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

    MyGraph graph(vertex_count);

    cout << "Введите данные о рёбрах для графа:\n";
    for (size_t i = 0; i < vertex_count; ++i) {
        for (size_t j = 0; j < vertex_count; ++j) {
            int edge_data;
            cin >> edge_data;
            if (edge_data != INF) {
                graph.addEdge(i, j, edge_data);
            }
        }
    }

    floydWarshall(graph);

    return 0;
}