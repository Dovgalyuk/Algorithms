#include <iostream>
#include <fstream>
#include <vector>

#include "queue.h"

typedef std::vector<std::vector<int>> Graph;

void bfs(const Graph& graph, int source) {
    size_t n = graph.size();
    std::vector<int> d(graph.size(), -1);
    
    d[source] = 0;

    Queue<int> queue;
    queue.insert(source);

    while (!queue.empty()) {
        int v = queue.get();
        queue.remove();
        for (size_t e = 0; e < n; e++) {
            if (graph[v][e] != 0 && d[e] == -1) {
                queue.insert(e);
                d[e] = d[v] + 1;
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

    Graph matrix(v, std::vector<int>(v));

    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            inputFile >> matrix[i][j];
        }
    }

    inputFile.close();

    bfs(matrix, 0);

    return 0;
}