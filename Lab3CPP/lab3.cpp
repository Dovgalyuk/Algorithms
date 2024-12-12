#include <iostream>
#include <fstream>
#include <vector>
#include "queue.h"

void bfs(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& distances) {
    Queue* queue = queue_create();
    queue_insert(queue, start);
    distances[start] = 0;

    while (!queue_empty(queue)) {
        int vertex = queue_get(queue);
        queue_remove(queue);

        for (size_t i = 0; i < graph[vertex].size(); ++i) {
            if (graph[vertex][i] == 1 && distances[i] == -1) {
                queue_insert(queue, i);
                distances[i] = distances[vertex] + 1;
            }
        }
    }

    queue_delete(queue);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    int n;
    infile >> n;
    std::vector<std::vector<int>> graph(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            infile >> graph[i][j];
        }
    }
    infile.close();

    std::vector<int> distances(n, -1);
    bfs(graph, 0, distances);

    std::ofstream outfile("output.txt");
    for (int distance : distances) {
        outfile << distance << std::endl;
    }
    outfile.close();

    return 0;
}
