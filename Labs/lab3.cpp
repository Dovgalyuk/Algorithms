#include <iostream>
#include "queue.h"

using namespace std;

int bfs(const int** graph, int num_vertices, int start, int finish, Queue* queue) {
    bool* visited = new bool[num_vertices];
    int* distance = new int[num_vertices];

    for (int i = 0; i < num_vertices; ++i) {
        visited[i] = false;
        distance[i] = -1;
    }

    visited[start] = true;
    distance[start] = 0;
    queue_insert(queue, start);

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);

        for (int i = 0; i < num_vertices; ++i) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = true;
                distance[i] = distance[current] + 1;
                queue_insert(queue, i);

                if (i == finish) {
                    int result = distance[i];
                    delete[] visited;
                    delete[] distance;
                    return result;
                }
            }
        }
    }

    delete[] visited;
    delete[] distance;
    return -1;
}

int main() {
    int n, start, finish;
    cin >> n >> start >> finish;
    start--; // Óìåíüøàåì íà 1, ÷òîáû èñïîëüçîâàòü íóìåðàöèþ ñ íóëÿ
    finish--;

    Queue* queue = queue_create();

    int** graph = new int* [n];
    for (int i = 0; i < n; ++i) {
        graph[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    int shortest_path_length = bfs((const int**)graph, n, start, finish, queue);

    if (shortest_path_length <= 0) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        cout << shortest_path_length << endl;
    }

    for (int i = 0; i < n; ++i) {
        delete[] graph[i];
    }
    delete[] graph;

    queue_delete(queue);

    return 0;
}