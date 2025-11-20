#include <iostream>
#include <fstream>
#include <vector>

#include "queue.h"

void bfs(const std::vector<std::vector<int>>& graph, int source) {
    size_t n = graph.size();
    std::vector<int> d(graph.size(), -1);
    std::vector<bool> visited(graph.size(), false);
    
    d[source] = 0;
    visited[source] = true;

    Queue<int> queue;
    queue.insert(source);

    while (!queue.empty()) {
        int v = queue.get();
        queue.remove();
        for (size_t e = 0; e < n; e++) {
            if (graph[v][e] != 0 && !visited[e]) {
                queue.insert(e);
                d[e] = d[v] + 1;
                visited[e] = true;
            }
        }
    }

    for (int i : d) {
        std::cout << i << std::endl;
    }
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        std::cerr << "Не хватает аргументов командной строки!" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);

    int v;
    inputFile >> v;

    std::vector<std::vector<int>> matrix(v, std::vector<int>(v));

    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            inputFile >> matrix[i][j];
        }
    }

    inputFile.close();

    bfs(matrix, 0);

    return 0;
}