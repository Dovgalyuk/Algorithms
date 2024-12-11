#include <iostream>
#include <fstream>
#include "queue.h"

using namespace std;

void bfs(int start, int finish, int n, int** graph, int* parent) {
    Queue* q = queue_create();
    bool* visited = new bool[n + 1];

    for (int i = 1; i <= n; ++i) {
        visited[i] = false;
    }

    queue_insert(q, start);
    visited[start] = true;

    while (!queue_empty(q)) {
        int current = queue_get(q);
        queue_remove(q);

        for (int i = 1; i <= n; ++i) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                parent[i] = current;
                queue_insert(q, i);

                if (i == finish) {
                    delete[] visited;
                    queue_delete(q);
                    return;
                }
            }
        }
    }
    queue_delete(q);
    delete[] visited;
}

int main(__attribute__((unused)) int argc, char** argv) {
    ifstream input(argv[1]);

    int n, start, finish;
    input >> n >> start >> finish;

    int** graph = new int*[n + 1];
    for (int i = 0; i <= n; ++i) {
        graph[i] = new int[n + 1]();
    }

    int u, v;
    while (input >> u >> v) {
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    int* parent = new int[n + 1];
    for (int i = 1; i <= n; ++i) {
        parent[i] = -1;
    }

    bfs(start, finish, n, graph, parent);

    if (parent[finish] == -1) {
        cout << "IMPOSSIBLE";
    } else {
        int path_length = 0;
        for (int at = finish; at != -1; at = parent[at]) {
            path_length++;
        }

        int* path = new int[path_length];
        int index = path_length - 1;
        for (int at = finish; at != -1; at = parent[at]) {
            path[index--] = at;
        }

        for (int i = 0; i < path_length; ++i) {
            if (i > 0) {
                cout << " ";
            }
            cout << path[i];
        }

        delete[] path;
    }

    for (int i = 0; i <= n; ++i) {
        delete[] graph[i];
    }
    delete[] graph;

    delete[] parent;

    return 0;
}
