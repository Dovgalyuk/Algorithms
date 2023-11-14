#include <iostream>
#include <vector>
#include "queue.h" // Подключаем вашу библиотеку queue

using namespace std;

int bfs(const std::vector<std::vector<int>>& graph, int start, int finish, Queue* queue) {
    vector<bool> visited(graph.size(), false);
    vector<int> distance(graph.size(), -1);

    visited[start] = true;
    distance[start] = 0;
    queue_insert(queue, start);

    while (!queue_empty(queue)) {
        int current = queue_get(queue);
        queue_remove(queue);

        for (size_t i = 0; i < graph[current].size(); ++i) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = true;
                distance[i] = distance[current] + 1;
                queue_insert(queue, static_cast<Data>(i));

                if (i == finish) {
                    return distance[i];
                }
            }
        }
    }

    return -1;
}

int main() {
    int n, start, finish;
    cin >> n >> start >> finish;
    start--; // Уменьшаем на 1, чтобы использовать нумерацию с нуля
    finish--;

    Queue* queue = queue_create();

    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    int shortest_path_length = bfs(graph, start, finish, queue);

    if (shortest_path_length == -1) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        cout << shortest_path_length << endl;
    }

    queue_delete(queue);

    return 0;
}