#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"

std::vector<int> bfs_distances(const std::vector<std::vector<int>>& graph, int start_vertex) {
    size_t n = graph.size();
    std::vector<int> distances(n, -1);
    distances[start_vertex] = 0;

    Queue* queue = queue_create();
    queue_insert(queue, start_vertex);

    while (!queue_empty(queue)) {
        int v = queue_get(queue);
        queue_remove_one(queue);

        for (size_t u = 0; u < n; ++u) {
            if (graph[v][u] == 1 && distances[u] == -1) {
                distances[u] = distances[v] + 1;
                queue_insert(queue, u);
            }
        }
    }

    queue_delete(queue);
    return distances;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Error opening input file\n";
        return 1;
    }

    std::ofstream output(argv[2], std::ios::out | std::ios::trunc);
    if (!output) {
        std::cerr << "Error opening output file\n";
        return 1;
    }

    int n;
    input >> n;
    std::vector<std::vector<int>> graph(n, std::vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            input >> graph[i][j];
        }
    }

    std::vector<int> distances = bfs_distances(graph, 0);

    for (int distance : distances) {
        output << distance << "\n";
    }

    input.close();
    output.close();

    return 0;
}