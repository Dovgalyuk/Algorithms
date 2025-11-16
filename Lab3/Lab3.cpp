#include "Lab3.h"

BFSResult bfs(int n, int start, int finish, Graph& graph) {
    IntVector dist(n, - 1);
    IntVector parent(n, -1);
    Queue<int> queue;

    dist[start] = 0;
    queue.insert(start);

    while (!queue.empty()) {
        auto cur = queue.get();
        queue.remove();

        if (cur == finish) break;

        for (auto neighbor : graph[cur]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[cur] + 1;
                parent[neighbor] = cur;
                queue.insert(neighbor);
            }
        }
    }

    return std::make_pair(dist, parent);
}